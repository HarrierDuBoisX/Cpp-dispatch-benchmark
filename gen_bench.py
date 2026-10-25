import os
import re

CONFIG = {
    "NUM_OBJECTS": 1_000_000,
    "POLY_TYPES": 16,
    "MULTI_WIDTH": 16,
    "DEEP_DEPTH": 16,
    "FAT_VTBL_SIZE": 64,

    # Container traversal order
    "RUN_SEQ_ACCESS": True,
    "RUN_RND_ACCESS": True,

    # Execution dependency mode:
    # - RUN_THROUGHPUT_MODE: independent iterations (sum += op(item, 1)), measures OoO throughput
    # - RUN_LATENCY_CHAIN:   dependent chain (acc = op(item, acc)), measures true call + memory latency
    "RUN_THROUGHPUT_MODE": True,
    "RUN_LATENCY_CHAIN":   False,

    # I-Cache pressure & linker /OPT:ICF prevention:
    # Expands unique instruction blocks per template type N inside compute_payload<N>
    "SIMULATE_ICACHE_PRESSURE": True,

    # Condition matrices (applied to all .hpp files in the cases/ directory)
    "SUITE_BASELINE_EQUAL":   True,   # Baseline: 64B, PolyRandom, InterleavedTrash 1:1
    "SUITE_ENTROPY_MATRIX":   True,   # Mono vs PolySorted vs PolyRandom
    "SUITE_HEAP_MATRIX":      True,   # Compact vs InterleavedTrash 1:1 vs JitterFragmented
    "SUITE_FOOTPRINT_MATRIX": True,   # 16B Compact vs 60B Split vs 64B Line vs 256B Heavy

    # Nanobench Tuning
    "BENCH_WARMUP": 3,
    "BENCH_EPOCHS": 7,
    "BENCH_MIN_EPOCH_ITERS": 15,
}

CASES_DIR = "cases"
REGISTER_PATTERN = re.compile(r"\bREGISTER_(?:VALUE_MATRIX|HEAP_MATRIX|CUSTOM_BENCH)\s*\(")

def cpp_bool(val):
    return "true" if val else "false"

def generate_config_header():
    content = f"""#pragma once
#include <cstddef>

namespace cfg {{
    inline constexpr size_t NUM_OBJECTS   = {CONFIG['NUM_OBJECTS']};
    inline constexpr size_t POLY_TYPES    = {CONFIG['POLY_TYPES']};
    inline constexpr size_t MULTI_WIDTH   = {CONFIG['MULTI_WIDTH']};
    inline constexpr size_t DEEP_DEPTH    = {CONFIG['DEEP_DEPTH']};
    inline constexpr size_t FAT_VTBL_SIZE = {CONFIG['FAT_VTBL_SIZE']};

    inline constexpr bool RUN_SEQ_ACCESS           = {cpp_bool(CONFIG['RUN_SEQ_ACCESS'])};
    inline constexpr bool RUN_RND_ACCESS           = {cpp_bool(CONFIG['RUN_RND_ACCESS'])};

    inline constexpr bool RUN_THROUGHPUT_MODE      = {cpp_bool(CONFIG['RUN_THROUGHPUT_MODE'])};
    inline constexpr bool RUN_LATENCY_CHAIN        = {cpp_bool(CONFIG['RUN_LATENCY_CHAIN'])};
    inline constexpr bool SIMULATE_ICACHE_PRESSURE = {cpp_bool(CONFIG['SIMULATE_ICACHE_PRESSURE'])};

    inline constexpr bool SUITE_BASELINE_EQUAL     = {cpp_bool(CONFIG['SUITE_BASELINE_EQUAL'])};
    inline constexpr bool SUITE_ENTROPY_MATRIX     = {cpp_bool(CONFIG['SUITE_ENTROPY_MATRIX'])};
    inline constexpr bool SUITE_HEAP_MATRIX        = {cpp_bool(CONFIG['SUITE_HEAP_MATRIX'])};
    inline constexpr bool SUITE_FOOTPRINT_MATRIX   = {cpp_bool(CONFIG['SUITE_FOOTPRINT_MATRIX'])};
}}
"""
    with open("bench_config.hpp", "w", encoding="utf-8") as f:
        f.write(content)

def discover_hpp_cases(folder=CASES_DIR):
    if not os.path.exists(folder):
        os.makedirs(folder)
        return []

    valid_files = []
    for filename in sorted(os.listdir(folder)):
        if not filename.endswith(".hpp"):
            continue
        filepath = os.path.join(folder, filename)
        with open(filepath, "r", encoding="utf-8") as f:
            source = f.read()
        if REGISTER_PATTERN.search(source):
            valid_files.append(f"{folder}/{filename}")
            print(f"  [+] Included C++ module: {filename}")
        else:
            print(f"  [!] Skipped {filename} (no REGISTER_* macro found)")
    return valid_files

def generate_runner(cpp_files):
    includes = "\n".join(f'#include "{path}"' for path in cpp_files)
    runner_code = f"""
// AUTOMATICALLY GENERATED UNITY BENCHMARK
#define ANKERL_NANOBENCH_IMPLEMENT
#include "bench_core.hpp"
#include "bench_stabilize.hpp"

#include <iostream>
#include <fstream>

{includes}

int main() {{

    bench_env::stabilize_environment();

    std::cout << "Objects: " << cfg::NUM_OBJECTS << " | Poly Types: " << cfg::POLY_TYPES << "\\n";

    bench_core::Environment env(cfg::NUM_OBJECTS, cfg::POLY_TYPES);

    ankerl::nanobench::Bench bench;
    bench.title("C++ Dispatch Matrix Benchmark")
         .unit("op")
         .batch(cfg::NUM_OBJECTS)
         .relative(true)
         .warmup({CONFIG['BENCH_WARMUP']})
         .epochs({CONFIG['BENCH_EPOCHS']})
         .minEpochIterations({CONFIG['BENCH_MIN_EPOCH_ITERS']});

    bench_core::Registry::run_all(bench, env);

    std::ofstream csv_file(".\\\\result\\\\benchmark_results.csv");
    ankerl::nanobench::render(ankerl::nanobench::templates::csv(), bench, csv_file);

    std::ofstream html_file(".\\\\result\\\\benchmark_results.html");
    ankerl::nanobench::render(ankerl::nanobench::templates::htmlBoxplot(), bench, html_file);

    return 0;
}}
"""
    with open("benchmark.cpp", "w", encoding="utf-8") as f:
        f.write(runner_code)

if __name__ == "__main__":
    generate_config_header()
    cases = discover_hpp_cases()
    generate_runner(cases)