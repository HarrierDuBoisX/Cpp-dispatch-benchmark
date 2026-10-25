#pragma once

#include "nanobench.h"
#include "bench_config.hpp"

#include <vector>
#include <memory>
#include <variant>
#include <random>
#include <algorithm>
#include <functional>
#include <utility>
#include <unordered_map>
#include <array>
#include <string>
#include <concepts>
#include <cstdint>
#include <cstddef>

#if defined(_MSC_VER)
    #define NOINLINE __declspec(noinline)
#else
    #define NOINLINE __attribute__((noinline))
#endif

namespace bench_core {

NOINLINE int do_payload(int val) {
    return (val ^ 0xDEADBEEF) + 1;
}

// Runtime type_idx overload (also expands instruction body when SIMULATE_ICACHE_PRESSURE is enabled)
inline int compute_payload(int val, int id, size_t type_idx) {
    int acc = val + id + static_cast<int>(type_idx);
    if constexpr (cfg::SIMULATE_ICACHE_PRESSURE) {
        acc ^= static_cast<int>((type_idx + 1) * 0x9E3779B1u);
        acc = (acc ^ (acc >> 13)) + static_cast<int>(type_idx * 0x85EBCA6Bu);
        acc ^= (acc << 7);
    }
    return do_payload(acc);
}

// Compile-time type_idx overload: generates a distinct machine code sequence for each N
// to prevent identical COMDAT folding (/OPT:ICF) and create realistic L1I cache footprint.
template <size_t N>
inline int compute_payload(int val, int id) {
    int acc = val + id + static_cast<int>(N);
    if constexpr (cfg::SIMULATE_ICACHE_PRESSURE) {
        constexpr std::uint32_t kSalt1 = static_cast<std::uint32_t>((N + 1) * 0x9E3779B1u);
        constexpr std::uint32_t kSalt2 = static_cast<std::uint32_t>((N + 1) * 0x85EBCA6Bu);
        constexpr std::uint32_t kSalt3 = static_cast<std::uint32_t>((N + 1) * 0xC2B2AE35u);
        acc ^= static_cast<int>(kSalt1);
        acc = (acc ^ (acc >> ((N % 7) + 1))) + static_cast<int>(kSalt2);
        acc ^= (acc << ((N % 5) + 1)) ^ static_cast<int>(kSalt3);
    }
    return do_payload(acc);
}

// ============================================================================
// TESTING CONDITIONS
// ============================================================================

enum class EntropyMode {
    Mono,        // Single active type (100% branch target predictor accuracy)
    PolySorted,  // 16 types, sorted in contiguous blocks
    PolyRandom   // 16 types in random order (BTB stress-test)
};

enum class HeapMode {
    Compact,          // Allocated sequentially without gaps
    InterleavedTrash, // Alternating 1:1 with dummy allocations
    JitterFragmented  // Random allocations (16..512 bytes) between objects
};

enum class FootprintMode {
    Compact16B,   // Minimal footprint without artificial padding (high cache density)
    Unaligned60B, // 60 bytes without 64B alignment (forces cache-line splits in arrays)
    Aligned64B,   // Exactly 1 cache line (64 bytes, 64-byte aligned)
    Heavy256B     // Exactly 4 cache lines (256 bytes, 64-byte aligned)
};

inline const char* to_string(EntropyMode m) {
    switch (m) {
        case EntropyMode::Mono:       return "Mono";
        case EntropyMode::PolySorted: return "PolySorted";
        case EntropyMode::PolyRandom: return "PolyRnd";
    }
    return "";
}

inline const char* to_string(HeapMode m) {
    switch (m) {
        case HeapMode::Compact:          return "HeapCompact";
        case HeapMode::InterleavedTrash: return "HeapTrash1to1";
        case HeapMode::JitterFragmented: return "HeapJitter";
    }
    return "";
}

inline const char* to_string(FootprintMode m) {
    switch (m) {
        case FootprintMode::Compact16B:   return "16B_Compact";
        case FootprintMode::Unaligned60B: return "60B_Split";
        case FootprintMode::Aligned64B:   return "64B_Line";
        case FootprintMode::Heavy256B:    return "256B_Heavy";
    }
    return "";
}

// ============================================================================
// DATA GEOMETRY GENERATOR (SIZE AND ALIGNMENT CONTROL)
// ============================================================================

template <FootprintMode Mode>
inline constexpr size_t target_alignment_v =
    (Mode == FootprintMode::Aligned64B || Mode == FootprintMode::Heavy256B)
        ? 64
        : alignof(void*);

template <size_t Bytes>
struct PaddingBlock {
    char pad[Bytes]{};
};
template <>
struct PaddingBlock<0> {};

template <FootprintMode Mode, size_t HeaderBytes = 0>
struct PayloadStorage;

template <size_t HeaderBytes>
struct PayloadStorage<FootprintMode::Compact16B, HeaderBytes> {
    int id = 0;
};

#pragma pack(push, 4)
template <size_t HeaderBytes>
struct PayloadStorage<FootprintMode::Unaligned60B, HeaderBytes> {
    static constexpr size_t TARGET = 60;
    static constexpr size_t PAD = (TARGET > HeaderBytes + 4) ? (TARGET - HeaderBytes - 4) : 0;
    int id = 0;
    PaddingBlock<PAD> pad{};
};
#pragma pack(pop)

template <size_t HeaderBytes>
struct PayloadStorage<FootprintMode::Aligned64B, HeaderBytes> {
    static constexpr size_t TARGET = 64;
    static constexpr size_t PAD = (TARGET > HeaderBytes + 4) ? (TARGET - HeaderBytes - 4) : 0;
    int id = 0;
    PaddingBlock<PAD> pad{};
};

template <size_t HeaderBytes>
struct PayloadStorage<FootprintMode::Heavy256B, HeaderBytes> {
    static constexpr size_t TARGET = 256;
    static constexpr size_t PAD = (TARGET > HeaderBytes + 4) ? (TARGET - HeaderBytes - 4) : 0;
    int id = 0;
    PaddingBlock<PAD> pad{};
};

// ============================================================================
// EXECUTION ENVIRONMENT AND PREGENERATED SEQUENCES
// ============================================================================

struct Environment {
    std::vector<size_t> types_mono;
    std::vector<size_t> types_sorted;
    std::vector<size_t> types_random;
    std::vector<int> rand_indices;
    std::vector<int> rand_indices_bucketed;
    std::vector<size_t> jitter_sizes;

    Environment(size_t num_objects, size_t poly_types)
        : types_mono(num_objects, 0),
          types_sorted(num_objects),
          types_random(num_objects),
          rand_indices(num_objects),
          rand_indices_bucketed(num_objects),
          jitter_sizes(num_objects)
    {
        std::mt19937 g(42);
        std::uniform_int_distribution<size_t> dist_type(0, poly_types - 1);
        std::uniform_int_distribution<size_t> dist_jitter(16, 512);

        for (size_t i = 0; i < num_objects; ++i) {
            types_random[i] = dist_type(g);
            rand_indices[i] = static_cast<int>(i);
            rand_indices_bucketed[i] = static_cast<int>(i);
            jitter_sizes[i] = dist_jitter(g);
        }

        types_sorted = types_random;
        std::sort(types_sorted.begin(), types_sorted.end());

        // Global shuffle for Mono and PolyRandom random memory access
        std::shuffle(rand_indices.begin(), rand_indices.end(), g);

        // Intra-bucket shuffle for PolySorted [Rnd]: randomizes memory positions
        // strictly within each contiguous type block so BTB predictability remains sorted.
        size_t block_start = 0;
        while (block_start < num_objects) {
            size_t block_end = block_start + 1;
            while (block_end < num_objects && types_sorted[block_end] == types_sorted[block_start]) {
                ++block_end;
            }
            std::shuffle(
                rand_indices_bucketed.begin() + static_cast<std::ptrdiff_t>(block_start),
                rand_indices_bucketed.begin() + static_cast<std::ptrdiff_t>(block_end),
                g);
            block_start = block_end;
        }
    }

    const std::vector<size_t>& get_types(EntropyMode mode) const {
        switch (mode) {
            case EntropyMode::Mono:       return types_mono;
            case EntropyMode::PolySorted: return types_sorted;
            case EntropyMode::PolyRandom: return types_random;
        }
        return types_random;
    }

    const std::vector<int>& get_rand_indices(EntropyMode mode) const {
        if (mode == EntropyMode::PolySorted) {
            return rand_indices_bucketed;
        }
        return rand_indices;
    }
};

template <typename Container, typename DispatchOp>
NOINLINE void execute_access_modes(
    ankerl::nanobench::Bench& bench,
    const Environment& env,
    EntropyMode entropy,
    const std::string& label,
    Container& data,
    DispatchOp op)
{
    const auto& r_indices = env.get_rand_indices(entropy);

    if constexpr (cfg::RUN_THROUGHPUT_MODE) {
        if constexpr (cfg::RUN_SEQ_ACCESS) {
            bench.run((label + " [Seq]").c_str(), [&]() {
                long long sum = 0;
                for (auto& item : data) {
                    sum += op(item, 1);
                }
                ankerl::nanobench::doNotOptimizeAway(sum);
            });
        }

        if constexpr (cfg::RUN_RND_ACCESS) {
            bench.run((label + " [Rnd]").c_str(), [&]() {
                long long sum = 0;
                for (int idx : r_indices) {
                    sum += op(data[static_cast<size_t>(idx)], 1);
                }
                ankerl::nanobench::doNotOptimizeAway(sum);
            });
        }
    }

    if constexpr (cfg::RUN_LATENCY_CHAIN) {
        if constexpr (cfg::RUN_SEQ_ACCESS) {
            bench.run((label + " [Seq-Lat]").c_str(), [&]() {
                int acc = 1;
                for (auto& item : data) {
                    acc = op(item, acc);
                }
                ankerl::nanobench::doNotOptimizeAway(acc);
            });
        }

        if constexpr (cfg::RUN_RND_ACCESS) {
            bench.run((label + " [Rnd-Lat]").c_str(), [&]() {
                int acc = 1;
                for (int idx : r_indices) {
                    acc = op(data[static_cast<size_t>(idx)], acc);
                }
                ankerl::nanobench::doNotOptimizeAway(acc);
            });
        }
    }
}

// ============================================================================
// CONCEPTS AND HARNESSES FOR VALUE AND HEAP TESTS
// ============================================================================

template <typename C>
concept ValueCaseConcept = requires(const typename C::Element& e, int id, size_t t) {
    typename C::Element;
    { C::make(id, t) } -> std::same_as<typename C::Element>;
    { C::dispatch(e, 1) } -> std::same_as<int>;
};

template <typename C>
concept HeapCaseConcept = requires(typename C::Handle& h, const typename C::Handle& ch, int id, size_t t) {
    typename C::Handle;
    { C::create(id, t) } -> std::same_as<typename C::Handle>;
    { C::destroy(h) } -> std::same_as<void>;
    { C::dispatch(ch, 1) } -> std::same_as<int>;
};

template <ValueCaseConcept Case>
void run_value_scenario(
    ankerl::nanobench::Bench& bench,
    const Environment& env,
    const std::string& base_name,
    EntropyMode entropy,
    FootprintMode footprint)
{
    const auto& types = env.get_types(entropy);
    std::vector<typename Case::Element> vec;
    vec.reserve(cfg::NUM_OBJECTS);

    for (size_t i = 0; i < cfg::NUM_OBJECTS; ++i) {
        vec.push_back(Case::make(static_cast<int>(i), types[i]));
    }

    std::string full_name = base_name + " | " + to_string(entropy) + " | " +
                            to_string(footprint) + " (" + std::to_string(sizeof(typename Case::Element)) + "B)";

    execute_access_modes(bench, env, entropy, full_name, vec, [](const typename Case::Element& elem, int v) {
        return Case::dispatch(elem, v);
    });
}

template <HeapCaseConcept Case>
void run_heap_scenario(
    ankerl::nanobench::Bench& bench,
    const Environment& env,
    const std::string& base_name,
    EntropyMode entropy,
    HeapMode heap_mode,
    FootprintMode footprint)
{
    // Allocate directly in the target entropy order so that [Seq] traversal
    // maintains consistent spatial heap locality across Mono, PolySorted, and PolyRandom.
    const auto& alloc_types = env.get_types(entropy);

    std::vector<typename Case::Handle> vec;
    std::vector<typename Case::Handle> trash_handles;
    std::vector<std::unique_ptr<char[]>> jitter_blocks;

    vec.reserve(cfg::NUM_OBJECTS);
    if (heap_mode == HeapMode::InterleavedTrash) {
        trash_handles.reserve(cfg::NUM_OBJECTS);
    } else if (heap_mode == HeapMode::JitterFragmented) {
        jitter_blocks.reserve(cfg::NUM_OBJECTS);
    }

    for (size_t i = 0; i < cfg::NUM_OBJECTS; ++i) {
        const int id = static_cast<int>(i);
        const size_t t_idx = alloc_types[i];

        if (heap_mode == HeapMode::JitterFragmented) {
            auto hole = std::make_unique<char[]>(env.jitter_sizes[i]);
            hole[0] = static_cast<char>(i);
            if (i % 3 != 0) {
                jitter_blocks.push_back(std::move(hole));
            }
        }

        vec.push_back(Case::create(id, t_idx));

        if (heap_mode == HeapMode::InterleavedTrash) {
            trash_handles.push_back(Case::create(id, t_idx));
        }
    }

    std::string size_suffix;
    if constexpr (requires { { Case::ObjectSize } -> std::convertible_to<size_t>; }) {
        size_suffix = " (" + std::to_string(Case::ObjectSize) + "B)";
    }

    std::string full_name = base_name + " | " + to_string(entropy) + " | " +
                            to_string(heap_mode) + " | " + to_string(footprint) + size_suffix;

    execute_access_modes(bench, env, entropy, full_name, vec, [](const typename Case::Handle& h, int v) {
        return Case::dispatch(h, v);
    });

    for (auto& h : vec) Case::destroy(h);
    for (auto& h : trash_handles) Case::destroy(h);
}

// ============================================================================
// AUTOMATIC RUNNER FOR CONDITION MATRICES (DEDUPLICATED, MONO-FIRST ORDER)
// ============================================================================

template <template <FootprintMode> class CaseTemplate>
void execute_value_matrix(ankerl::nanobench::Bench& bench, const Environment& env, const char* name) {
    if constexpr (cfg::SUITE_ENTROPY_MATRIX) {
        run_value_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::Mono, FootprintMode::Aligned64B);
        run_value_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::PolySorted, FootprintMode::Aligned64B);
        run_value_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::PolyRandom, FootprintMode::Aligned64B);
    } else if constexpr (cfg::SUITE_BASELINE_EQUAL) {
        run_value_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::PolyRandom, FootprintMode::Aligned64B);
    }

    if constexpr (cfg::SUITE_FOOTPRINT_MATRIX) {
        run_value_scenario<CaseTemplate<FootprintMode::Compact16B>>(
            bench, env, name, EntropyMode::PolyRandom, FootprintMode::Compact16B);
        run_value_scenario<CaseTemplate<FootprintMode::Unaligned60B>>(
            bench, env, name, EntropyMode::PolyRandom, FootprintMode::Unaligned60B);
        if constexpr (!cfg::SUITE_ENTROPY_MATRIX && !cfg::SUITE_BASELINE_EQUAL) {
            run_value_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
                bench, env, name, EntropyMode::PolyRandom, FootprintMode::Aligned64B);
        }
        run_value_scenario<CaseTemplate<FootprintMode::Heavy256B>>(
            bench, env, name, EntropyMode::PolyRandom, FootprintMode::Heavy256B);
    }
}

template <template <FootprintMode> class CaseTemplate>
void execute_heap_matrix(ankerl::nanobench::Bench& bench, const Environment& env, const char* name) {
    if constexpr (cfg::SUITE_ENTROPY_MATRIX) {
        run_heap_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::Mono, HeapMode::InterleavedTrash, FootprintMode::Aligned64B);
        run_heap_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::PolySorted, HeapMode::InterleavedTrash, FootprintMode::Aligned64B);
        run_heap_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::PolyRandom, HeapMode::InterleavedTrash, FootprintMode::Aligned64B);
    } else if constexpr (cfg::SUITE_BASELINE_EQUAL) {
        run_heap_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::PolyRandom, HeapMode::InterleavedTrash, FootprintMode::Aligned64B);
    }

    if constexpr (cfg::SUITE_HEAP_MATRIX) {
        run_heap_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::PolyRandom, HeapMode::Compact, FootprintMode::Aligned64B);
        if constexpr (!cfg::SUITE_ENTROPY_MATRIX && !cfg::SUITE_BASELINE_EQUAL) {
            run_heap_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
                bench, env, name, EntropyMode::PolyRandom, HeapMode::InterleavedTrash, FootprintMode::Aligned64B);
        }
        run_heap_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
            bench, env, name, EntropyMode::PolyRandom, HeapMode::JitterFragmented, FootprintMode::Aligned64B);
    }

    if constexpr (cfg::SUITE_FOOTPRINT_MATRIX) {
        run_heap_scenario<CaseTemplate<FootprintMode::Compact16B>>(
            bench, env, name, EntropyMode::PolyRandom, HeapMode::InterleavedTrash, FootprintMode::Compact16B);
        run_heap_scenario<CaseTemplate<FootprintMode::Unaligned60B>>(
            bench, env, name, EntropyMode::PolyRandom, HeapMode::InterleavedTrash, FootprintMode::Unaligned60B);
        if constexpr (!cfg::SUITE_ENTROPY_MATRIX && !cfg::SUITE_BASELINE_EQUAL && !cfg::SUITE_HEAP_MATRIX) {
            run_heap_scenario<CaseTemplate<FootprintMode::Aligned64B>>(
                bench, env, name, EntropyMode::PolyRandom, HeapMode::InterleavedTrash, FootprintMode::Aligned64B);
        }
        run_heap_scenario<CaseTemplate<FootprintMode::Heavy256B>>(
            bench, env, name, EntropyMode::PolyRandom, HeapMode::InterleavedTrash, FootprintMode::Heavy256B);
    }
}

template <typename HandleT, template <size_t> class Maker, size_t... Is>
constexpr auto make_factory_table(std::index_sequence<Is...>) {
    using Fn = HandleT (*)(int);
    return std::array<Fn, sizeof...(Is)>{ +[](int id) -> HandleT { return Maker<Is>::create(id); }... };
}

// ============================================================================
// TEST REGISTRY
// ============================================================================

using BenchEntryFn = void (*)(ankerl::nanobench::Bench&, const Environment&);

struct Registry {
    struct Item { std::string name; BenchEntryFn fn; };
    static std::vector<Item>& items() { static std::vector<Item> list; return list; }
    static void add(const char* name, BenchEntryFn fn) { items().push_back({name, fn}); }
    static void run_all(ankerl::nanobench::Bench& bench, const Environment& env) {
        for (const auto& item : items()) item.fn(bench, env);
    }
};

struct Registrar {
    Registrar(const char* name, BenchEntryFn fn) { Registry::add(name, fn); }
};

} // namespace bench_core

#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)

#define REGISTER_VALUE_MATRIX(CaseTemplate, BenchName) \
    static ::bench_core::Registrar CONCAT(_reg_v_, __COUNTER__)( \
        BenchName, \
        +[](ankerl::nanobench::Bench& b, const ::bench_core::Environment& e) { \
            ::bench_core::execute_value_matrix<CaseTemplate>(b, e, BenchName); \
        })

#define REGISTER_HEAP_MATRIX(CaseTemplate, BenchName) \
    static ::bench_core::Registrar CONCAT(_reg_h_, __COUNTER__)( \
        BenchName, \
        +[](ankerl::nanobench::Bench& b, const ::bench_core::Environment& e) { \
            ::bench_core::execute_heap_matrix<CaseTemplate>(b, e, BenchName); \
        })

#define REGISTER_CUSTOM_BENCH(BenchName, LambdaFn) \
    static ::bench_core::Registrar CONCAT(_reg_c_, __COUNTER__)(BenchName, LambdaFn)