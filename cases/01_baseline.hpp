#pragma once

#include "../bench_core.hpp"

namespace case_01_baseline {

using bench_core::FootprintMode;

template <FootprintMode Mode>
struct DirectObject {
    bench_core::PayloadStorage<Mode, 4> storage;
    int type_idx = 0;

    NOINLINE int update(int val) const {
        return bench_core::compute_payload(val, storage.id, static_cast<size_t>(type_idx));
    }
};

template <FootprintMode Mode>
struct DirectValueCase {
    using Element = DirectObject<Mode>;

    static Element make(int id, size_t type_idx) {
        Element e{};
        e.storage.id = id;
        e.type_idx = static_cast<int>(type_idx);
        return e;
    }

    static int dispatch(const Element& e, int val) {
        return e.update(val);
    }
};

struct SoASystem {
    std::vector<int> ids;
    std::vector<int> types;

    void init(const bench_core::Environment& env) {
        ids.resize(cfg::NUM_OBJECTS);
        types.resize(cfg::NUM_OBJECTS);
        for (size_t i = 0; i < cfg::NUM_OBJECTS; ++i) {
            ids[i] = static_cast<int>(i);
            types[i] = static_cast<int>(env.types_random[i]);
        }
    }

    NOINLINE long long update_all(int val) const {
        long long sum = 0;
        for (size_t i = 0; i < cfg::NUM_OBJECTS; ++i) {
            sum += bench_core::compute_payload(val, ids[i], static_cast<size_t>(types[i]));
        }
        return sum;
    }
};

REGISTER_VALUE_MATRIX(DirectValueCase, "01 Baseline: Direct Call (AoS)");

REGISTER_CUSTOM_BENCH("01 Baseline: SoA", +[](ankerl::nanobench::Bench& bench, const bench_core::Environment& env) {
    SoASystem soa;
    soa.init(env);
    bench.run("01 Baseline: SoA (Data Oriented) [Seq]", [&]() {
        ankerl::nanobench::doNotOptimizeAway(soa.update_all(1));
    });
});

} // namespace case_01_baseline