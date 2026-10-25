#pragma once

#include "../bench_core.hpp"

#if defined(_MSC_VER)
    #define BENCH_EMPTY_BASES __declspec(empty_bases)
#else
    #define BENCH_EMPTY_BASES
#endif

namespace case_05_crtp {

using bench_core::FootprintMode;

template <FootprintMode Mode>
inline constexpr size_t crtp_value_alignment_v =
    (Mode == FootprintMode::Aligned64B || Mode == FootprintMode::Heavy256B) ? 64 : 4;

template <typename Derived>
struct BENCH_EMPTY_BASES CRTP_Mono_Base {
    inline int interface_call(int v) const {
        return static_cast<const Derived*>(this)->impl(v);
    }
};

template <FootprintMode Mode>
struct BENCH_EMPTY_BASES alignas(crtp_value_alignment_v<Mode>) CRTP_Mono
    : public CRTP_Mono_Base<CRTP_Mono<Mode>> {
    bench_core::PayloadStorage<Mode, 4> storage;
    int type_idx = 0;

    NOINLINE int impl(int v) const {
        return bench_core::compute_payload(v, storage.id, static_cast<size_t>(type_idx));
    }
};

static_assert(sizeof(CRTP_Mono<FootprintMode::Compact16B>) == 8, "Compact16B CRTP_Mono must be 8 bytes");
static_assert(sizeof(CRTP_Mono<FootprintMode::Unaligned60B>) == 60, "Unaligned60B CRTP_Mono must be 60 bytes");
static_assert(sizeof(CRTP_Mono<FootprintMode::Aligned64B>) == 64, "Aligned64B CRTP_Mono must be 64 bytes");
static_assert(sizeof(CRTP_Mono<FootprintMode::Heavy256B>) == 256, "Heavy256B CRTP_Mono must be 256 bytes");

template <FootprintMode Mode>
struct CRTPMonoCase {
    using Element = CRTP_Mono<Mode>;
    static Element make(int id, size_t type_idx) {
        Element e{};
        e.storage.id = id;
        e.type_idx = static_cast<int>(type_idx);
        return e;
    }
    static int dispatch(const Element& e, int val) { return e.interface_call(val); }
};

template <typename Derived, size_t N>
struct BENCH_EMPTY_BASES CRTP_Mixin {
    inline int mixin_func(int v) const {
        return static_cast<const Derived*>(this)->impl_mixin(v, N);
    }
};


template <typename Derived, size_t... Is>
struct BENCH_EMPTY_BASES CRTP_MixinPack : public CRTP_Mixin<Derived, Is>... {};

template <typename Derived, typename Seq>
struct BENCH_EMPTY_BASES CRTP_Bases;

template <typename Derived, size_t... Is>
struct BENCH_EMPTY_BASES CRTP_Bases<Derived, std::index_sequence<Is...>>
    : public CRTP_MixinPack<Derived, Is...> {};

static_assert(sizeof(CRTP_Bases<void, std::make_index_sequence<cfg::MULTI_WIDTH>>) == 1,
              "Empty CRTP_Bases hierarchy must collapse to 1 byte via EBO");

template <FootprintMode Mode>
struct BENCH_EMPTY_BASES alignas(crtp_value_alignment_v<Mode>) CRTP_Wide
    : public CRTP_Bases<CRTP_Wide<Mode>, std::make_index_sequence<cfg::MULTI_WIDTH>> {
    bench_core::PayloadStorage<Mode, 0> storage;

    NOINLINE int impl_mixin(int v, size_t n) const {
        return bench_core::compute_payload(v, storage.id, n);
    }
};

static_assert(sizeof(CRTP_Wide<FootprintMode::Compact16B>) == 4, "Compact16B CRTP_Wide must be 4 bytes (EBO)");
static_assert(sizeof(CRTP_Wide<FootprintMode::Unaligned60B>) == 60, "Unaligned60B CRTP_Wide must be 60 bytes");
static_assert(sizeof(CRTP_Wide<FootprintMode::Aligned64B>) == 64, "Aligned64B CRTP_Wide must be 64 bytes");
static_assert(sizeof(CRTP_Wide<FootprintMode::Heavy256B>) == 256, "Heavy256B CRTP_Wide must be 256 bytes");

template <FootprintMode Mode>
struct CRTPWideCase {
    using Element = CRTP_Wide<Mode>;
    static Element make(int id, size_t) {
        Element e{};
        e.storage.id = id;
        return e;
    }
    static int dispatch(const Element& e, int val) {
        return e.template CRTP_Mixin<Element, cfg::MULTI_WIDTH - 1>::mixin_func(val);
    }
};

REGISTER_VALUE_MATRIX(CRTPMonoCase, "05 CRTP: Simple");
REGISTER_VALUE_MATRIX(CRTPWideCase, "05.1 CRTP: Wide Mixin");

} // namespace case_05_crtp