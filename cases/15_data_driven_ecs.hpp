#pragma once

#include "../bench_core.hpp"

namespace case_15_data_driven_ecs {

using bench_core::FootprintMode;

template <FootprintMode Mode>
inline constexpr size_t ecs_value_alignment_v =
    (Mode == FootprintMode::Aligned64B || Mode == FootprintMode::Heavy256B) ? 64 : 4;

// ============================================================================
// 1. DATA-DRIVEN TABLE DISPATCH (Replacing code polymorphism with a data LUT)
// ============================================================================
struct alignas(64) TypeBehaviorTable {
    std::array<int, cfg::POLY_TYPES> type_offsets{};

    constexpr TypeBehaviorTable() {
        for (size_t i = 0; i < cfg::POLY_TYPES; ++i) {
            type_offsets[i] = static_cast<int>(i);
        }
    }
};

inline constexpr TypeBehaviorTable G_BEHAVIOR_LUT{};

template <FootprintMode Mode>
struct alignas(ecs_value_alignment_v<Mode>) DataDrivenObject {
    std::uint8_t type_tag = 0;
    bench_core::PayloadStorage<Mode, 4> storage;

    NOINLINE int update(int val) const {
        const int type_param = G_BEHAVIOR_LUT.type_offsets[type_tag];
        return bench_core::compute_payload(val, storage.id, static_cast<size_t>(type_param));
    }
};

static_assert(sizeof(DataDrivenObject<FootprintMode::Compact16B>) == 8, "Compact16B DataDrivenObject must be 8 bytes");
static_assert(sizeof(DataDrivenObject<FootprintMode::Unaligned60B>) == 60, "Unaligned60B DataDrivenObject must be 60 bytes");
static_assert(sizeof(DataDrivenObject<FootprintMode::Aligned64B>) == 64, "Aligned64B DataDrivenObject must be 64 bytes");
static_assert(sizeof(DataDrivenObject<FootprintMode::Heavy256B>) == 256, "Heavy256B DataDrivenObject must be 256 bytes");

template <FootprintMode Mode>
struct DataDrivenValueCase {
    using Element = DataDrivenObject<Mode>;

    static Element make(int id, size_t t) {
        Element e{};
        e.type_tag = static_cast<std::uint8_t>(t % cfg::POLY_TYPES);
        e.storage.id = id;
        return e;
    }

    static int dispatch(const Element& e, int val) {
        return e.update(val);
    }
};

// ============================================================================
// 2. ECS ARCHETYPE BUCKET DISPATCH (AoS Homogeneous Type Pools without vptr)
// ============================================================================
template <FootprintMode Mode, size_t N>
struct alignas(ecs_value_alignment_v<Mode>) ArchetypeComponent {
    bench_core::PayloadStorage<Mode, 0> storage;

    NOINLINE int update(int val) const {
        return bench_core::compute_payload<N>(val, storage.id);
    }
};

static_assert(sizeof(ArchetypeComponent<FootprintMode::Compact16B, 0>) == 4, "Compact16B ArchetypeComponent must be 4 bytes");
static_assert(sizeof(ArchetypeComponent<FootprintMode::Unaligned60B, 0>) == 60, "Unaligned60B ArchetypeComponent must be 60 bytes");
static_assert(sizeof(ArchetypeComponent<FootprintMode::Aligned64B, 0>) == 64, "Aligned64B ArchetypeComponent must be 64 bytes");
static_assert(sizeof(ArchetypeComponent<FootprintMode::Heavy256B, 0>) == 256, "Heavy256B ArchetypeComponent must be 256 bytes");

template <FootprintMode Mode, typename Seq>
struct ArchetypeWorld;

template <FootprintMode Mode, size_t... Is>
struct ArchetypeWorld<Mode, std::index_sequence<Is...>> {
    std::tuple<std::vector<ArchetypeComponent<Mode, Is>>...> buckets;

    template <size_t N>
    void add_entity(int id) {
        ArchetypeComponent<Mode, N> comp{};
        comp.storage.id = id;
        std::get<N>(buckets).push_back(comp);
    }

    void init(const bench_core::Environment& env) {
        using AddFn = void (*)(ArchetypeWorld*, int);
        static constexpr std::array<AddFn, sizeof...(Is)> adders = {
            +[](ArchetypeWorld* w, int id) { w->add_entity<Is>(id); }...
        };

        for (size_t i = 0; i < cfg::NUM_OBJECTS; ++i) {
            size_t t = env.types_random[i] % sizeof...(Is);
            adders[t](this, static_cast<int>(i));
        }
    }

    template <size_t N>
    NOINLINE long long update_bucket(int val) const {
        long long sum = 0;
        for (const auto& comp : std::get<N>(buckets)) {
            sum += comp.update(val);
        }
        return sum;
    }

    NOINLINE long long update_all_archetypes(int val) const {
        return (update_bucket<Is>(val) + ...);
    }
};

template <FootprintMode Mode>
void run_ecs_archetype_scenario(ankerl::nanobench::Bench& bench, const bench_core::Environment& env) {
    ArchetypeWorld<Mode, std::make_index_sequence<cfg::POLY_TYPES>> world;
    world.init(env);

    constexpr size_t comp_size = sizeof(ArchetypeComponent<Mode, 0>);
    std::string label = std::string("35 ECS: Archetype Buckets (AoS) | ") +
                        bench_core::to_string(Mode) + " (" + std::to_string(comp_size) + "B) [Seq]";

    bench.run(label.c_str(), [&]() {
        ankerl::nanobench::doNotOptimizeAway(world.update_all_archetypes(1));
    });
}

// ============================================================================
// 3. ECS SoA HOT/COLD SPLIT (Structure of Arrays: 4B Hot IDs separated from Cold Data)
// ============================================================================
template <FootprintMode Mode>
struct ColdComponentBlock {
    static constexpr size_t kTotalBytes = sizeof(ArchetypeComponent<Mode, 0>);
    static constexpr size_t kColdBytes = (kTotalBytes > sizeof(int)) ? (kTotalBytes - sizeof(int)) : 0;
    bench_core::PaddingBlock<kColdBytes> cold_pad{};
};

template <FootprintMode Mode, size_t N>
struct SoAArchetypeBucket {
    std::vector<int> hot_ids;
    std::vector<ColdComponentBlock<Mode>> cold_data;

    void add(int id) {
        hot_ids.push_back(id);
        cold_data.emplace_back();
    }

    static NOINLINE int process_hot_id(int id, int val) {
        return bench_core::compute_payload<N>(val, id);
    }

    NOINLINE long long update_hot_stream(int val) const {
        long long sum = 0;
        for (int id : hot_ids) {
            sum += process_hot_id(id, val);
        }
        return sum;
    }
};

template <FootprintMode Mode, typename Seq>
struct SoAArchetypeWorld;

template <FootprintMode Mode, size_t... Is>
struct SoAArchetypeWorld<Mode, std::index_sequence<Is...>> {
    std::tuple<SoAArchetypeBucket<Mode, Is>...> buckets;

    void init(const bench_core::Environment& env) {
        using AddFn = void (*)(SoAArchetypeWorld*, int);
        static constexpr std::array<AddFn, sizeof...(Is)> adders = {
            +[](SoAArchetypeWorld* w, int id) { std::get<Is>(w->buckets).add(id); }...
        };

        for (size_t i = 0; i < cfg::NUM_OBJECTS; ++i) {
            size_t t = env.types_random[i] % sizeof...(Is);
            adders[t](this, static_cast<int>(i));
        }
    }

    NOINLINE long long update_all_soa(int val) const {
        return (std::get<Is>(buckets).update_hot_stream(val) + ...);
    }
};

template <FootprintMode Mode>
void run_ecs_soa_scenario(ankerl::nanobench::Bench& bench, const bench_core::Environment& env) {
    SoAArchetypeWorld<Mode, std::make_index_sequence<cfg::POLY_TYPES>> world;
    world.init(env);

    constexpr size_t total_size = sizeof(ArchetypeComponent<Mode, 0>);
    std::string label = std::string("15.0 ECS: SoA Hot/Cold Split (4B Hot Stream) | ") +
                        bench_core::to_string(Mode) + " (" + std::to_string(total_size) + "B Total) [Seq]";

    bench.run(label.c_str(), [&]() {
        ankerl::nanobench::doNotOptimizeAway(world.update_all_soa(1));
    });
}

REGISTER_VALUE_MATRIX(DataDrivenValueCase, "15.1 Data-Driven: Branchless Parameter LUT");

REGISTER_CUSTOM_BENCH("15.2 ECS: Archetype Buckets (AoS)", +[](ankerl::nanobench::Bench& bench, const bench_core::Environment& env) {
    if constexpr (cfg::SUITE_ENTROPY_MATRIX || cfg::SUITE_BASELINE_EQUAL) {
        run_ecs_archetype_scenario<FootprintMode::Aligned64B>(bench, env);
    }
    if constexpr (cfg::SUITE_FOOTPRINT_MATRIX) {
        run_ecs_archetype_scenario<FootprintMode::Compact16B>(bench, env);
        run_ecs_archetype_scenario<FootprintMode::Unaligned60B>(bench, env);
        if constexpr (!cfg::SUITE_ENTROPY_MATRIX && !cfg::SUITE_BASELINE_EQUAL) {
            run_ecs_archetype_scenario<FootprintMode::Aligned64B>(bench, env);
        }
        run_ecs_archetype_scenario<FootprintMode::Heavy256B>(bench, env);
    }
});

REGISTER_CUSTOM_BENCH("15.3 ECS: SoA Hot/Cold Split", +[](ankerl::nanobench::Bench& bench, const bench_core::Environment& env) {
    if constexpr (cfg::SUITE_ENTROPY_MATRIX || cfg::SUITE_BASELINE_EQUAL) {
        run_ecs_soa_scenario<FootprintMode::Aligned64B>(bench, env);
    }
    if constexpr (cfg::SUITE_FOOTPRINT_MATRIX) {
        run_ecs_soa_scenario<FootprintMode::Compact16B>(bench, env);
        run_ecs_soa_scenario<FootprintMode::Unaligned60B>(bench, env);
        if constexpr (!cfg::SUITE_ENTROPY_MATRIX && !cfg::SUITE_BASELINE_EQUAL) {
            run_ecs_soa_scenario<FootprintMode::Aligned64B>(bench, env);
        }
        run_ecs_soa_scenario<FootprintMode::Heavy256B>(bench, env);
    }
});

} // namespace case_15_data_driven_ecs