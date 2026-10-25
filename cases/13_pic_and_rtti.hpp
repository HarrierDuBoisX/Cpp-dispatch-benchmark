#pragma once

#include "../bench_core.hpp"
#include <any>

namespace case_13_pic_and_rtti {

using bench_core::FootprintMode;

struct PolyBase {
    virtual ~PolyBase() = default;
    virtual int update(int val) = 0;
};

template <FootprintMode Mode, size_t N>
struct alignas(bench_core::target_alignment_v<Mode>) PolyDerived : public PolyBase {
    bench_core::PayloadStorage<Mode, sizeof(PolyBase)> storage;
    explicit PolyDerived(int id) { storage.id = id; }

    NOINLINE int update_direct(int val) const {
        return bench_core::compute_payload<N>(val, storage.id);
    }

    NOINLINE int update(int val) override {
        return bench_core::compute_payload<N>(val, storage.id);
    }
};

static_assert(sizeof(PolyDerived<FootprintMode::Aligned64B, 0>) == 64, "Aligned64B PolyDerived must be 64 bytes");
static_assert(sizeof(PolyDerived<FootprintMode::Heavy256B, 0>) == 256, "Heavy256B PolyDerived must be 256 bytes");

// ============================================================================
// 1. POLYMORPHIC INLINE CACHE (Bimorphic vptr Guard + Virtual Fallback)
// ============================================================================
template <FootprintMode Mode>
struct BimorphicPICHeapCase {
    using Handle = PolyBase*;
    static constexpr size_t ObjectSize = sizeof(PolyDerived<Mode, 0>);

    template <size_t N>
    struct Maker {
        static Handle create(int id) {
            return new PolyDerived<Mode, N>(id);
        }
    };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl =
            bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }

    static void destroy(Handle h) { delete h; }

    static inline const void* get_vptr(const PolyBase* p) noexcept {
        return *reinterpret_cast<const void* const*>(p);
    }

    static int dispatch(Handle h, int val) {
        static const PolyDerived<Mode, 0> proto0(0);
        static const PolyDerived<Mode, 1> proto1(0);
        static const void* const vptr0 = get_vptr(&proto0);
        static const void* const vptr1 = get_vptr(&proto1);

        const void* const obj_vptr = get_vptr(h);
        if (obj_vptr == vptr0) [[likely]] {
            return static_cast<const PolyDerived<Mode, 0>*>(h)->update_direct(val);
        }
        if (obj_vptr == vptr1) {
            return static_cast<const PolyDerived<Mode, 1>*>(h)->update_direct(val);
        }
        return h->update(val);
    }
};

// ============================================================================
// 2. RTTI DYNAMIC_CAST CASCADE (Type resolution via RTTI tables)
// ============================================================================
template <FootprintMode Mode>
struct DynamicCastHeapCase {
    using Handle = PolyBase*;
    static constexpr size_t ObjectSize = sizeof(PolyDerived<Mode, 0>);

    template <size_t N>
    struct Maker {
        static Handle create(int id) { return new PolyDerived<Mode, N>(id); }
    };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl =
            bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }

    static void destroy(Handle h) { delete h; }

    template <size_t N = 0>
    static inline int try_cast(Handle h, int val) {
        if (auto* d = dynamic_cast<PolyDerived<Mode, N>*>(h)) {
            return d->update_direct(val);
        }
        if constexpr (N + 1 < cfg::POLY_TYPES) {
            return try_cast<N + 1>(h, val);
        } else {
            return 0;
        }
    }

    static int dispatch(Handle h, int val) {
        return try_cast<0>(h, val);
    }
};

// ============================================================================
// 3. STD::ANY + STD::ANY_CAST (In-Place SBO vs Payload-Scaled)
// ============================================================================
template <size_t N>
struct AnySboPayload {
    int id = 0;

    NOINLINE int eval(int val) const {
        return bench_core::compute_payload<N>(val, id);
    }
};

template <FootprintMode Mode>
struct StdAnyInPlaceSBOCase {
    using Element = std::any;

    template <size_t N>
    struct Maker {
        static Element create(int id) {
            return std::make_any<AnySboPayload<N>>(AnySboPayload<N>{id});
        }
    };

    static Element make(int id, size_t t) {
        static constexpr auto tbl =
            bench_core::make_factory_table<Element, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }

    template <size_t N = 0>
    static inline int try_any_cast(const Element& a, int val) {
        if (const auto* p = std::any_cast<AnySboPayload<N>>(&a)) {
            return p->eval(val);
        }
        if constexpr (N + 1 < cfg::POLY_TYPES) {
            return try_any_cast<N + 1>(a, val);
        } else {
            return 0;
        }
    }

    static int dispatch(const Element& a, int val) {
        return try_any_cast<0>(a, val);
    }
};

template <FootprintMode Mode, size_t N>
struct AnyPayload {
    bench_core::PayloadStorage<Mode, 0> storage;

    NOINLINE int eval(int val) const {
        return bench_core::compute_payload<N>(val, storage.id);
    }
};

template <FootprintMode Mode>
struct StdAnyValueCase {
    using Element = std::any;

    template <size_t N>
    struct Maker {
        static Element create(int id) {
            AnyPayload<Mode, N> p{};
            p.storage.id = id;
            return std::make_any<AnyPayload<Mode, N>>(p);
        }
    };

    static Element make(int id, size_t t) {
        static constexpr auto tbl =
            bench_core::make_factory_table<Element, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }

    template <size_t N = 0>
    static inline int try_any_cast(const Element& a, int val) {
        if (const auto* p = std::any_cast<AnyPayload<Mode, N>>(&a)) {
            return p->eval(val);
        }
        if constexpr (N + 1 < cfg::POLY_TYPES) {
            return try_any_cast<N + 1>(a, val);
        } else {
            return 0;
        }
    }

    static int dispatch(const Element& a, int val) {
        return try_any_cast<0>(a, val);
    }
};

REGISTER_HEAP_MATRIX(BimorphicPICHeapCase,    "13.1 PIC: Speculative Bimorphic Inline Cache");
REGISTER_HEAP_MATRIX(DynamicCastHeapCase,     "13.2 RTTI: dynamic_cast Cascade");
REGISTER_VALUE_MATRIX(StdAnyInPlaceSBOCase,   "13.3 RTTI: std::any (In-Place SBO)");
REGISTER_VALUE_MATRIX(StdAnyValueCase,        "13.4 RTTI: std::any (Payload-Scaled)");

} // namespace case_13_pic_and_rtti