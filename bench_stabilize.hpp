#pragma once

#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <vector>
#include <iostream>
#include <cstdint>

namespace bench_env {

struct CoreCandidate {
    uint8_t efficiency_class = 0;
    bool has_smt = false;
    uint16_t group = 0;
    KAFFINITY affinity_mask = 0;
};

inline void disable_power_throttling(HANDLE thread) {
    THREAD_POWER_THROTTLING_STATE throttling_state{};
    throttling_state.Version = THREAD_POWER_THROTTLING_CURRENT_VERSION;
    throttling_state.ControlMask = THREAD_POWER_THROTTLING_EXECUTION_SPEED;
    throttling_state.StateMask = 0; // 0 = Force frequency throttling off

    SetThreadInformation(
        thread,
        ThreadPowerThrottling,
        &throttling_state,
        sizeof(throttling_state)
    );
}

inline bool stabilize_environment() {
    HANDLE process = GetCurrentProcess();
    HANDLE thread  = GetCurrentThread();

    // 1. Elevating the Priority of Processes and Workflows
    if (!SetPriorityClass(process, HIGH_PRIORITY_CLASS)) {
        std::cerr << "[!] SetPriorityClass failed. Error: " << GetLastError() << "\n";
    }
    if (!SetThreadPriority(thread, THREAD_PRIORITY_HIGHEST)) {
        std::cerr << "[!] SetThreadPriority failed. Error: " << GetLastError() << "\n";
    }

    // Setting the base priority (disabling dynamic boost by the OS)
    SetThreadPriorityBoost(thread, TRUE);

    // Disabling Energy-Saving Throttling (EcoQoS / Speed Shift throttling)
    disable_power_throttling(thread);

    // Reading the Allowed System Mask of the Process (for group 0)
    DWORD_PTR proc_mask = 0;
    DWORD_PTR sys_mask  = 0;
    bool has_proc_mask  = GetProcessAffinityMask(process, &proc_mask, &sys_mask) != 0;

    // Reading the Physical Topology of Cores
    DWORD buffer_size = 0;
    GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &buffer_size);
    if (buffer_size == 0) {
        std::cerr << "[!] GetLogicalProcessorInformationEx size query failed. Error: " 
                  << GetLastError() << "\n";
        return false;
    }

    std::vector<uint8_t> buffer(buffer_size);
    auto* info = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.data());

    if (!GetLogicalProcessorInformationEx(RelationProcessorCore, info, &buffer_size)) {
        std::cerr << "[!] GetLogicalProcessorInformationEx failed. Error: " 
                  << GetLastError() << "\n";
        return false;
    }

    std::vector<CoreCandidate> cores;
    uint8_t max_efficiency_class = 0;

    DWORD offset = 0;
    while (offset < buffer_size) {
        auto* record = reinterpret_cast<PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX>(buffer.data() + offset);

        if (record->Relationship == RelationProcessorCore && record->Processor.GroupCount > 0) {
            CoreCandidate cand{};
            cand.efficiency_class = record->Processor.EfficiencyClass;
            cand.has_smt = (record->Processor.Flags & LTP_PC_SMT) != 0;
            cand.group = record->Processor.GroupMask[0].Group;
            cand.affinity_mask = record->Processor.GroupMask[0].Mask;

            // We only consider the kernels that are permitted for the current process
            if (cand.group == 0 && has_proc_mask) {
                cand.affinity_mask &= proc_mask;
            }

            if (cand.affinity_mask != 0) {
                if (cand.efficiency_class > max_efficiency_class) {
                    max_efficiency_class = cand.efficiency_class;
                }
                cores.push_back(cand);
            }
        }
        offset += record->Size;
    }

    if (cores.empty()) {
        std::cerr << "[!] No available CPU cores found.\n";
        return false;
    }

    // 5. Selecting the P-core (by skipping physical core 0 in group 0, where the DPC/ISR are located)
    CoreCandidate* selected_core = nullptr;
    const KAFFINITY core0_mask = cores[0].affinity_mask;

    for (auto& core : cores) {
        if (core.efficiency_class == max_efficiency_class) {
            bool is_core_zero = (core.group == 0) && (core.affinity_mask == core0_mask);
            if (!is_core_zero) {
                selected_core = &core;
                break;
            }
        }
    }

    // Fallback: If only one P-core is available, we use it
    if (!selected_core) {
        for (auto& core : cores) {
            if (core.efficiency_class == max_efficiency_class) {
                selected_core = &core;
                break;
            }
        }
    }

    // Isolation of a single hardware thread without sign overflow (UB-free)
    KAFFINITY mask = selected_core->affinity_mask;
    KAFFINITY single_thread_mask = mask & (~mask + 1ULL);

    // Binding the thread through GROUP_AFFINITY (works correctly for both 1 and >1 groups)
    GROUP_AFFINITY group_affinity{};
    group_affinity.Group = selected_core->group;
    group_affinity.Mask  = single_thread_mask;

    if (!SetThreadGroupAffinity(thread, &group_affinity, nullptr)) {
        std::cerr << "[!] SetThreadGroupAffinity failed. Error: " << GetLastError() << "\n";
        return false;
    }

    // Forcing a quantum yield to make the scheduler immediately move the thread to the selected core
    SwitchToThread();

    std::cout << "[+] CPU Environment Stabilized:\n"
              << "    - EfficiencyClass : " << static_cast<int>(selected_core->efficiency_class)
              << (max_efficiency_class > 0 ? " (P-Core)\n" : " (Homogeneous Core)\n")
              << "    - Processor Group : " << selected_core->group << "\n"
              << "    - Logical Core Bit: 0x" << std::hex << single_thread_mask << std::dec << "\n"
              << "    - SMT Isolated    : " << (selected_core->has_smt ? "Yes" : "No") << "\n";

    return true;
}

} // namespace bench_env

#else

namespace bench_env {
inline bool stabilize_environment() {
    return true;
}
} // namespace bench_env

#endif