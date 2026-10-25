#pragma once

#include "../bench_core.hpp"

namespace case_08_pointers {

using bench_core::FootprintMode;

struct PtrBase {
    virtual ~PtrBase() = default;
    virtual int update(int v) = 0;
};

template <FootprintMode Mode, size_t N>
struct alignas(bench_core::target_alignment_v<Mode>) PtrDerived : public PtrBase {
    bench_core::PayloadStorage<Mode, sizeof(PtrBase)> storage;
    explicit PtrDerived(int id) { storage.id = id; }
    NOINLINE int update(int v) override {
        return bench_core::compute_payload(v, storage.id, N);
    }
};

static_assert(sizeof(PtrDerived<FootprintMode::Aligned64B, 0>) == 64, "Aligned64B PtrDerived must be 64 bytes");
static_assert(sizeof(PtrDerived<FootprintMode::Heavy256B, 0>) == 256, "Heavy256B PtrDerived must be 256 bytes");

template <FootprintMode Mode>
struct UniquePtrHeapCase {
    using Handle = std::unique_ptr<PtrBase>;
    static constexpr size_t ObjectSize = sizeof(PtrDerived<Mode, 0>);

    template <size_t N>
    struct Maker { static Handle create(int id) { return std::make_unique<PtrDerived<Mode, N>>(id); } };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static void destroy(Handle& h) { h.reset(); }
    static int dispatch(const Handle& h, int val) { return h->update(val); }
};

template <FootprintMode Mode>
struct SharedPtrHeapCase {
    using Handle = std::shared_ptr<PtrBase>;
    static constexpr size_t ObjectSize = sizeof(PtrDerived<Mode, 0>);

    template <size_t N>
    struct Maker { static Handle create(int id) { return std::make_shared<PtrDerived<Mode, N>>(id); } };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static void destroy(Handle& h) { h.reset(); }
    static int dispatch(const Handle& h, int val) { return h->update(val); }
};

// Pointer to a non-virtual member function of a class (int (Obj::*)(int) const)
template <FootprintMode Mode>
struct alignas(bench_core::target_alignment_v<Mode>) MemPtrSimpleObj {
    using MemFn = int (MemPtrSimpleObj::*)(int) const;
    MemFn fn_ptr = nullptr;
    bench_core::PayloadStorage<Mode, sizeof(MemFn)> storage;

    template <size_t N>
    NOINLINE int method_impl(int v) const {
        return bench_core::compute_payload(v, storage.id, N);
    }
};

#pragma pack(push, 4)
template <>
struct MemPtrSimpleObj<FootprintMode::Unaligned60B> {
    using MemFn = int (MemPtrSimpleObj::*)(int) const;
    MemFn fn_ptr = nullptr;
    bench_core::PayloadStorage<FootprintMode::Unaligned60B, sizeof(MemFn)> storage;

    template <size_t N>
    NOINLINE int method_impl(int v) const {
        return bench_core::compute_payload(v, storage.id, N);
    }
};
#pragma pack(pop)

static_assert(sizeof(MemPtrSimpleObj<FootprintMode::Unaligned60B>) == 60, "Unaligned60B MemPtrSimpleObj must be 60 bytes");
static_assert(sizeof(MemPtrSimpleObj<FootprintMode::Aligned64B>) == 64, "Aligned64B MemPtrSimpleObj must be 64 bytes");
static_assert(sizeof(MemPtrSimpleObj<FootprintMode::Heavy256B>) == 256, "Heavy256B MemPtrSimpleObj must be 256 bytes");

template <FootprintMode Mode>
struct MemPtrSimpleCase {
    using Element = MemPtrSimpleObj<Mode>;

    template <size_t N>
    struct Maker {
        static Element create(int id) {
            Element e{};
            e.storage.id = id;
            e.fn_ptr = &Element::template method_impl<N>;
            return e;
        }
    };

    static Element make(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Element, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static int dispatch(const Element& e, int val) { return (e.*(e.fn_ptr))(val); }
};

// Pointer to a class's virtual member function (called via a vcall thunk)
struct MemVirtBase {
    virtual ~MemVirtBase() = default;
    virtual int virt_method(int v) const = 0;
};

template <FootprintMode Mode, size_t N>
struct alignas(bench_core::target_alignment_v<Mode>) MemVirtDerived : public MemVirtBase {
    bench_core::PayloadStorage<Mode, sizeof(MemVirtBase)> storage;
    explicit MemVirtDerived(int id) { storage.id = id; }
    NOINLINE int virt_method(int v) const override {
        return bench_core::compute_payload(v, storage.id, N);
    }
};

static_assert(sizeof(MemVirtDerived<FootprintMode::Aligned64B, 0>) == 64, "Aligned64B MemVirtDerived must be 64 bytes");
static_assert(sizeof(MemVirtDerived<FootprintMode::Heavy256B, 0>) == 256, "Heavy256B MemVirtDerived must be 256 bytes");

template <FootprintMode Mode>
struct MemPtrVirtHeapCase {
    using Handle = MemVirtBase*;
    static constexpr size_t ObjectSize = sizeof(MemVirtDerived<Mode, 0>);

    template <size_t N>
    struct Maker { static Handle create(int id) { return new MemVirtDerived<Mode, N>(id); } };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static void destroy(Handle h) { delete h; }
    static int dispatch(Handle h, int val) {
        using VirtMemFn = int (MemVirtBase::*)(int) const;
        VirtMemFn pmf = &MemVirtBase::virt_method;
        return (h->*pmf)(val);
    }
};

REGISTER_HEAP_MATRIX(UniquePtrHeapCase,  "08.1 Pointers: std::unique_ptr");
REGISTER_HEAP_MATRIX(SharedPtrHeapCase,  "08.2 Pointers: std::shared_ptr");
REGISTER_VALUE_MATRIX(MemPtrSimpleCase,  "08.3 Pointers: Member Ptr (Non-Virtual)");
REGISTER_HEAP_MATRIX(MemPtrVirtHeapCase, "08.4 Pointers: Member Ptr (Virtual vcall)");

} // namespace case_08_pointers