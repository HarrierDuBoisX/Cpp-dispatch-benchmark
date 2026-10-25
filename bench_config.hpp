#pragma once
#include <cstddef>

namespace cfg {
    inline constexpr size_t NUM_OBJECTS   = 1000000;
    inline constexpr size_t POLY_TYPES    = 16;
    inline constexpr size_t MULTI_WIDTH   = 16;
    inline constexpr size_t DEEP_DEPTH    = 16;
    inline constexpr size_t FAT_VTBL_SIZE = 64;

    inline constexpr bool RUN_SEQ_ACCESS           = true;
    inline constexpr bool RUN_RND_ACCESS           = true;

    inline constexpr bool RUN_THROUGHPUT_MODE      = true;
    inline constexpr bool RUN_LATENCY_CHAIN        = false;
    inline constexpr bool SIMULATE_ICACHE_PRESSURE = true;

    inline constexpr bool SUITE_BASELINE_EQUAL     = true;
    inline constexpr bool SUITE_ENTROPY_MATRIX     = true;
    inline constexpr bool SUITE_HEAP_MATRIX        = true;
    inline constexpr bool SUITE_FOOTPRINT_MATRIX   = true;
}
