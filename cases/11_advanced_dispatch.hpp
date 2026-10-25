#pragma once

#include "../bench_core.hpp"
#include <immintrin.h>
#include <limits>
#include <concepts>

#ifdef _MSC_VER
#include <intrin.h>
static inline int get_tzcnt(unsigned int mask) {
    unsigned long idx; _BitScanForward(&idx, mask); return static_cast<int>(idx);
}
static inline int get_tzcnt_sz(std::size_t mask) {
    unsigned long idx;
#ifdef _WIN64
    _BitScanForward64(&idx, mask);
#else
    _BitScanForward(&idx, static_cast<unsigned long>(mask));
#endif
    return static_cast<int>(idx);
}
#else
static inline int get_tzcnt(unsigned int mask) { return __builtin_ctz(mask); }
static inline int get_tzcnt_sz(std::size_t mask) {
    return (sizeof(std::size_t) == sizeof(std::uint64_t)) ? __builtin_ctzll(mask) : __builtin_ctz(mask);
}
#endif

namespace case_11_advanced {

using bench_core::FootprintMode;
using AdvKeyT = std::uint32_t;
using AdvFuncT = int (*)(int, int);

inline constexpr std::size_t kDefaultMaxCapacity =
    std::size_t{1} << std::numeric_limits<std::uint8_t>::digits;
inline constexpr std::uint64_t kFibonacciHashMultiplier64 = 0x9E3779B97F4A7C15ull;
inline constexpr AdvKeyT kKeyPrimeStride = 1337u;
inline constexpr AdvKeyT kKeyDomainMask =
    static_cast<AdvKeyT>(std::numeric_limits<std::uint16_t>::max());

template <FootprintMode Mode>
inline constexpr size_t adv_value_alignment_v =
    (Mode == FootprintMode::Aligned64B || Mode == FootprintMode::Heavy256B) ? 64 : alignof(AdvKeyT);

template <typename K, typename F>
struct AdvEntry {
    K key;
    F handler;
};

template <std::size_t MaxCapacity = kDefaultMaxCapacity>
struct AdvDispatchBuilder {
    std::array<AdvEntry<AdvKeyT, AdvFuncT>, MaxCapacity> entries{};
    std::size_t count = 0;

    constexpr AdvDispatchBuilder& add(AdvKeyT key, AdvFuncT h) {
        if (count < MaxCapacity) entries[count++] = {key, h};
        return *this;
    }
};

template <auto BuilderData, auto DefaultHandler>
struct AdvDispatcherBase {
    static constexpr std::size_t COUNT = BuilderData.count;
    using IndexT = std::conditional_t<
        (COUNT < std::numeric_limits<std::uint8_t>::max()),
        std::uint8_t,
        std::uint16_t>;
    static constexpr IndexT MISS_FUNC = static_cast<IndexT>(COUNT);

    static constexpr auto extract_handlers() {
        std::array<AdvFuncT, COUNT + 1> arr{};
        for (std::size_t i = 0; i < COUNT; ++i) arr[i] = BuilderData.entries[i].handler;
        arr[COUNT] = DefaultHandler;
        return arr;
    }
    alignas(64) static constexpr auto HANDLERS = extract_handlers();
};

// ============================================================================
// 1. FLAT DIRECT LOOKUP TABLE (Parameterized by LutKeyT: uint8_t or uint16_t)
// ============================================================================
template <auto BuilderData, auto DefaultHandler, std::unsigned_integral LutKeyT = std::uint16_t>
class FastDispatcherLUT : public AdvDispatcherBase<BuilderData, DefaultHandler> {
    using Base = AdvDispatcherBase<BuilderData, DefaultHandler>;
    using Base::COUNT;
    using Base::MISS_FUNC;
    using Base::HANDLERS;
    using typename Base::IndexT;

    static constexpr std::size_t KEY_BITS = std::numeric_limits<LutKeyT>::digits;
    static constexpr std::size_t LUT_SIZE = std::size_t{1} << KEY_BITS;
    static constexpr AdvKeyT KEY_MASK = static_cast<AdvKeyT>(std::numeric_limits<LutKeyT>::max());

    static_assert(COUNT <= LUT_SIZE, "Number of registered handlers exceeds FlatLUT capacity");

    struct FlatLUT {
        std::array<IndexT, LUT_SIZE> entries;
    };

    static constexpr FlatLUT build_lut() {
        FlatLUT lut{};
        lut.entries.fill(MISS_FUNC);
        for (std::size_t i = 0; i < COUNT; ++i) {
            const std::size_t slot = static_cast<std::size_t>(BuilderData.entries[i].key & KEY_MASK);
            if (lut.entries[slot] != MISS_FUNC) {
                throw "Compile-time key collision detected in FastDispatcherLUT";
            }
            lut.entries[slot] = static_cast<IndexT>(i);
        }
        return lut;
    }

    alignas(64) static constexpr FlatLUT TABLE = build_lut();

public:
    template <typename... Args>
    static inline decltype(auto) dispatch(AdvKeyT key, Args&&... args) {
        return HANDLERS[TABLE.entries[key & KEY_MASK]](std::forward<Args>(args)...);
    }
};

// ============================================================================
// 2. MULTIPLICATIVE HASH TABLE WITH LINEAR PROBING
// ============================================================================
template <auto BuilderData, auto DefaultHandler>
class FastDispatcherHash : public AdvDispatcherBase<BuilderData, DefaultHandler> {
    using Base = AdvDispatcherBase<BuilderData, DefaultHandler>;
    using Base::COUNT;
    using Base::MISS_FUNC;
    using Base::HANDLERS;
    using typename Base::IndexT;

    static constexpr std::size_t TABLE_SIZE = []() constexpr {
        std::size_t n = (COUNT == 0) ? 2 : COUNT * 2;
        std::size_t p = 1;
        while (p < n) p <<= 1;
        return p;
    }();

    static constexpr std::size_t SHIFT = []() constexpr {
        std::size_t v = TABLE_SIZE;
        std::size_t log2_size = 0;
        while ((v & 1) == 0) {
            log2_size++;
            v >>= 1;
        }
        return std::numeric_limits<std::uint64_t>::digits - log2_size;
    }();

    static constexpr std::size_t MASK = TABLE_SIZE - 1;

    struct HashData {
        std::array<AdvKeyT, TABLE_SIZE> keys{};
        std::array<IndexT, TABLE_SIZE> values{};
    };

    static constexpr HashData build_hash() {
        HashData table{};
        table.values.fill(MISS_FUNC);
        for (std::size_t i = 0; i < COUNT; ++i) {
            AdvKeyT key = BuilderData.entries[i].key;
            std::size_t idx = static_cast<std::size_t>((static_cast<std::uint64_t>(key) * kFibonacciHashMultiplier64) >> SHIFT);
            while (table.values[idx] != MISS_FUNC) {
                idx = (idx + 1) & MASK;
            }
            table.keys[idx] = key;
            table.values[idx] = static_cast<IndexT>(i);
        }
        return table;
    }

    alignas(64) static constexpr HashData TABLE = build_hash();

public:
    template <typename... Args>
    static inline decltype(auto) dispatch(AdvKeyT key, Args&&... args) {
        std::size_t idx = static_cast<std::size_t>((static_cast<std::uint64_t>(key) * kFibonacciHashMultiplier64) >> SHIFT);
        while (TABLE.values[idx] != MISS_FUNC) {
            if (TABLE.keys[idx] == key) [[likely]] {
                return HANDLERS[TABLE.values[idx]](std::forward<Args>(args)...);
            }
            idx = (idx + 1) & MASK;
        }
        return HANDLERS[MISS_FUNC](std::forward<Args>(args)...);
    }
};

// ============================================================================
// 3. AVX2 SIMD PARALLEL KEY SEARCH
// ============================================================================
template <auto BuilderData, auto DefaultHandler>
class FastDispatcherAVX2 : public AdvDispatcherBase<BuilderData, DefaultHandler> {
    using Base = AdvDispatcherBase<BuilderData, DefaultHandler>;
    using Base::COUNT;
    using Base::MISS_FUNC;
    using Base::HANDLERS;
    using typename Base::IndexT;

    static constexpr std::size_t AVX2_LANES = sizeof(__m256i) / sizeof(AdvKeyT);
    static constexpr std::size_t LANE_MASK = AVX2_LANES - 1;
    static constexpr std::size_t SIMD_COUNT = (COUNT + LANE_MASK) & ~LANE_MASK;
    static constexpr AdvKeyT EMPTY_KEY_SENTINEL = std::numeric_limits<AdvKeyT>::max();

    struct alignas(sizeof(__m256i)) SimdData {
        std::array<AdvKeyT, SIMD_COUNT> keys{};
        std::array<IndexT, SIMD_COUNT> values{};
    };

    static constexpr SimdData build_simd() {
        SimdData table{};
        table.keys.fill(EMPTY_KEY_SENTINEL);
        table.values.fill(MISS_FUNC);
        for (std::size_t i = 0; i < COUNT; ++i) {
            table.keys[i] = BuilderData.entries[i].key;
            table.values[i] = static_cast<IndexT>(i);
        }
        return table;
    }

    alignas(64) static constexpr SimdData TABLE = build_simd();

public:
    template <typename... Args>
    static inline decltype(auto) dispatch(AdvKeyT key, Args&&... args) {
        __m256i target = _mm256_set1_epi32(static_cast<int>(key));
        for (std::size_t i = 0; i < SIMD_COUNT; i += AVX2_LANES) {
            __m256i data = _mm256_load_si256(reinterpret_cast<const __m256i*>(&TABLE.keys[i]));
            __m256i cmp = _mm256_cmpeq_epi32(target, data);
            int mask = _mm256_movemask_ps(_mm256_castsi256_ps(cmp));
            if (mask != 0) [[likely]] {
                int bit_idx = get_tzcnt(static_cast<unsigned int>(mask));
                return HANDLERS[TABLE.values[i + static_cast<std::size_t>(bit_idx)]](std::forward<Args>(args)...);
            }
        }
        return HANDLERS[MISS_FUNC](std::forward<Args>(args)...);
    }
};

// ============================================================================
// 4. BRANCHLESS BINARY SEARCH
// ============================================================================
template <auto BuilderData, auto DefaultHandler>
class FastDispatcherBinSearch : public AdvDispatcherBase<BuilderData, DefaultHandler> {
    using Base = AdvDispatcherBase<BuilderData, DefaultHandler>;
    using Base::COUNT;
    using Base::MISS_FUNC;
    using Base::HANDLERS;
    using typename Base::IndexT;

    struct alignas(64) BinData {
        std::array<AdvKeyT, COUNT> keys{};
        std::array<IndexT, COUNT> values{};
    };

    static constexpr BinData build_bin() {
        std::array<std::size_t, COUNT> indices{};
        for (std::size_t i = 0; i < COUNT; ++i) indices[i] = i;
        for (std::size_t i = 0; i < COUNT; ++i) {
            for (std::size_t j = i + 1; j < COUNT; ++j) {
                if (BuilderData.entries[indices[i]].key > BuilderData.entries[indices[j]].key) {
                    std::size_t tmp = indices[i];
                    indices[i] = indices[j];
                    indices[j] = tmp;
                }
            }
        }
        BinData table{};
        for (std::size_t i = 0; i < COUNT; ++i) {
            table.keys[i] = BuilderData.entries[indices[i]].key;
            table.values[i] = static_cast<IndexT>(indices[i]);
        }
        return table;
    }

    alignas(64) static constexpr BinData TABLE = build_bin();

public:
    template <typename... Args>
    static inline decltype(auto) dispatch(AdvKeyT key, Args&&... args) {
        std::size_t base = 0;
        std::size_t len = COUNT;
        while (len > 1) {
            std::size_t half = len / 2;
            base += (TABLE.keys[base + half - 1] < key) ? half : 0;
            len -= half;
        }
        if (TABLE.keys[base] == key) [[likely]] {
            return HANDLERS[TABLE.values[base]](std::forward<Args>(args)...);
        }
        return HANDLERS[MISS_FUNC](std::forward<Args>(args)...);
    }
};

// ============================================================================
// 5. EYTZINGER (BFS-LAYOUT) SEARCH TREE
// ============================================================================
template <auto BuilderData, auto DefaultHandler>
class FastDispatcherEytzinger : public AdvDispatcherBase<BuilderData, DefaultHandler> {
    using Base = AdvDispatcherBase<BuilderData, DefaultHandler>;
    using Base::COUNT;
    using Base::MISS_FUNC;
    using Base::HANDLERS;
    using typename Base::IndexT;

    struct alignas(64) EytzData {
        std::array<AdvKeyT, COUNT + 1> keys{};
        std::array<IndexT, COUNT + 1> values{};
    };

    static constexpr void eytz_build(
        const std::array<std::size_t, COUNT>& sorted_indices,
        EytzData& table,
        std::size_t i,
        std::size_t& k)
    {
        if (i <= COUNT) {
            eytz_build(sorted_indices, table, 2 * i, k);
            std::size_t orig_idx = sorted_indices[k++];
            table.keys[i] = BuilderData.entries[orig_idx].key;
            table.values[i] = static_cast<IndexT>(orig_idx);
            eytz_build(sorted_indices, table, 2 * i + 1, k);
        }
    }

    static constexpr EytzData build_eytz() {
        std::array<std::size_t, COUNT> indices{};
        for (std::size_t i = 0; i < COUNT; ++i) indices[i] = i;
        for (std::size_t i = 0; i < COUNT; ++i) {
            for (std::size_t j = i + 1; j < COUNT; ++j) {
                if (BuilderData.entries[indices[i]].key > BuilderData.entries[indices[j]].key) {
                    std::size_t tmp = indices[i];
                    indices[i] = indices[j];
                    indices[j] = tmp;
                }
            }
        }
        EytzData table{};
        std::size_t k = 0;
        eytz_build(indices, table, 1, k);
        return table;
    }

    alignas(64) static constexpr EytzData TABLE = build_eytz();

public:
    template <typename... Args>
    static inline decltype(auto) dispatch(AdvKeyT key, Args&&... args) {
        std::size_t k = 1;
        while (k <= COUNT) {
            k = 2 * k + (TABLE.keys[k] < key ? 1 : 0);
        }
        k >>= (get_tzcnt_sz(~k) + 1);
        if (k != 0 && TABLE.keys[k] == key) [[likely]] {
            return HANDLERS[TABLE.values[k]](std::forward<Args>(args)...);
        }
        return HANDLERS[MISS_FUNC](std::forward<Args>(args)...);
    }
};

// ============================================================================
// BENCHMARK CASE WIRING
// ============================================================================

template <size_t N>
NOINLINE int adv_handler(int val, int id) {
    return bench_core::compute_payload(val, id, N);
}

NOINLINE int adv_miss(int, int) {
    return 0;
}

constexpr AdvKeyT make_sparse_key(std::size_t type_idx) noexcept {
    return static_cast<AdvKeyT>((type_idx * kKeyPrimeStride) & kKeyDomainMask);
}

template <size_t... Is>
constexpr auto build_advanced_map(std::index_sequence<Is...>) {
    AdvDispatchBuilder<kDefaultMaxCapacity> b{};
    ((b.add(make_sparse_key(Is), &adv_handler<Is>)), ...);
    return b;
}

constexpr auto advanced_map = build_advanced_map(std::make_index_sequence<cfg::POLY_TYPES>{});

using DispLUT8      = FastDispatcherLUT<advanced_map, &adv_miss, std::uint8_t>;
using DispLUT16     = FastDispatcherLUT<advanced_map, &adv_miss, std::uint16_t>;
using DispHash      = FastDispatcherHash<advanced_map, &adv_miss>;
using DispAVX2      = FastDispatcherAVX2<advanced_map, &adv_miss>;
using DispBinSearch = FastDispatcherBinSearch<advanced_map, &adv_miss>;
using DispEytzinger = FastDispatcherEytzinger<advanced_map, &adv_miss>;

template <FootprintMode Mode>
struct alignas(adv_value_alignment_v<Mode>) AdvPacketElement {
    AdvKeyT key = 0;
    bench_core::PayloadStorage<Mode, sizeof(AdvKeyT)> storage;
};

static_assert(sizeof(AdvPacketElement<FootprintMode::Compact16B>) == 8, "Compact16B AdvPacketElement must be 8 bytes");
static_assert(sizeof(AdvPacketElement<FootprintMode::Unaligned60B>) == 60, "Unaligned60B AdvPacketElement must be 60 bytes");
static_assert(sizeof(AdvPacketElement<FootprintMode::Aligned64B>) == 64, "Aligned64B AdvPacketElement must be 64 bytes");
static_assert(sizeof(AdvPacketElement<FootprintMode::Heavy256B>) == 256, "Heavy256B AdvPacketElement must be 256 bytes");

template <FootprintMode Mode, typename Dispatcher>
struct AdvDispatchCase {
    using Element = AdvPacketElement<Mode>;

    static Element make(int id, size_t t) {
        Element e{};
        e.key = make_sparse_key(t % cfg::POLY_TYPES);
        e.storage.id = id;
        return e;
    }

    static int dispatch(const Element& e, int val) {
        return Dispatcher::dispatch(e.key, val, e.storage.id);
    }
};

template <FootprintMode Mode> using CaseLUT8      = AdvDispatchCase<Mode, DispLUT8>;
template <FootprintMode Mode> using CaseLUT16     = AdvDispatchCase<Mode, DispLUT16>;
template <FootprintMode Mode> using CaseHash      = AdvDispatchCase<Mode, DispHash>;
template <FootprintMode Mode> using CaseAVX2      = AdvDispatchCase<Mode, DispAVX2>;
template <FootprintMode Mode> using CaseBinSearch = AdvDispatchCase<Mode, DispBinSearch>;
template <FootprintMode Mode> using CaseEytzinger = AdvDispatchCase<Mode, DispEytzinger>;

REGISTER_VALUE_MATRIX(CaseLUT8,      "11.1 Advanced: Flat LUT (8-bit, 256B)");
REGISTER_VALUE_MATRIX(CaseLUT16,     "11.2 Advanced: Flat LUT (16-bit, 64KB)");
REGISTER_VALUE_MATRIX(CaseHash,      "11.3 Advanced: Hash (Linear Probe)");
REGISTER_VALUE_MATRIX(CaseAVX2,      "11.4 Advanced: AVX2 SIMD Search");
REGISTER_VALUE_MATRIX(CaseBinSearch, "11.5 Advanced: Branchless BinSearch");
REGISTER_VALUE_MATRIX(CaseEytzinger, "11.6 Advanced: Eytzinger BFS Search");

} // namespace case_11_advanced