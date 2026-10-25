#pragma once

#include "../bench_core.hpp"
#include <new>

namespace case_02_virtual {

using bench_core::FootprintMode;

// ============================================================================
// 02. Standard Polymorphic Virtual Dispatch
// ============================================================================

struct Base {
    virtual ~Base() = default;
    virtual int update(int val) = 0;
};

template <FootprintMode Mode, size_t N>
struct alignas(bench_core::target_alignment_v<Mode>) Poly : public Base {
    bench_core::PayloadStorage<Mode, sizeof(Base)> storage;

    explicit Poly(int id) { storage.id = id; }

    NOINLINE int update(int val) override {
        return bench_core::compute_payload(val, storage.id, N);
    }
};

static_assert(sizeof(Poly<FootprintMode::Aligned64B, 0>) == 64, "Aligned64B Poly must be exactly 64 bytes");
static_assert(sizeof(Poly<FootprintMode::Heavy256B, 0>) == 256, "Heavy256B Poly must be exactly 256 bytes");

template <FootprintMode Mode>
struct VirtualHeapCase {
    using Handle = Base*;
    static constexpr size_t ObjectSize = sizeof(Poly<Mode, 0>);

    template <size_t N>
    struct Maker {
        static Handle create(int id) { return new Poly<Mode, N>(id); }
    };

    static Handle create(int id, size_t type_idx) {
        static constexpr auto table =
            bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return table[type_idx % cfg::POLY_TYPES](id);
    }

    static void destroy(Handle h) { delete h; }
    static int dispatch(Handle h, int val) { return h->update(val); }
};

// ============================================================================
// 02.1 Deep Inheritance Chain
// ============================================================================

struct DeepBase {
    virtual ~DeepBase() = default;
    virtual int update(int v) = 0;
};

template <size_t Depth>
struct DeepLvl : public DeepLvl<Depth - 1> {
    NOINLINE int update(int v) override { return DeepLvl<Depth - 1>::update(v) + 1; }
};

template <>
struct DeepLvl<0> : public DeepBase {
    NOINLINE int update(int v) override { return v; }
};

template <FootprintMode Mode, size_t PolyIdx>
struct alignas(bench_core::target_alignment_v<Mode>) DeepLeaf : public DeepLvl<cfg::DEEP_DEPTH> {
    bench_core::PayloadStorage<Mode, sizeof(DeepLvl<cfg::DEEP_DEPTH>)> storage;
    explicit DeepLeaf(int id) { storage.id = id; }

    NOINLINE int update(int v) override {
        return bench_core::compute_payload(DeepLvl<cfg::DEEP_DEPTH>::update(v), storage.id, PolyIdx);
    }
};

static_assert(sizeof(DeepLeaf<FootprintMode::Aligned64B, 0>) == 64, "Aligned64B DeepLeaf must be 64 bytes");
static_assert(sizeof(DeepLeaf<FootprintMode::Heavy256B, 0>) == 256, "Heavy256B DeepLeaf must be 256 bytes");

template <FootprintMode Mode>
struct DeepHeapCase {
    using Handle = DeepBase*;
    static constexpr size_t ObjectSize = sizeof(DeepLeaf<Mode, 0>);

    template <size_t N>
    struct Maker { static Handle create(int id) { return new DeepLeaf<Mode, N>(id); } };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static void destroy(Handle h) { delete h; }
    static int dispatch(Handle h, int val) { return h->update(val); }
};

// ============================================================================
// 02.2 Multiple Inheritance (Non-Zero Base Offset / Adjustor Thunks)
// ============================================================================

template <size_t Branch>
struct MultiBaseBranch {
    virtual ~MultiBaseBranch() = default;
    virtual int update(int v) = 0;
    long long branch_pad = 0;
};

using TargetMultiBase = MultiBaseBranch<cfg::MULTI_WIDTH - 1>;

template <FootprintMode Mode, size_t PolyIdx, typename Seq = std::make_index_sequence<cfg::MULTI_WIDTH>>
struct MultiDerived;

template <FootprintMode Mode, size_t PolyIdx, size_t... Is>
struct alignas(bench_core::target_alignment_v<Mode>) MultiDerived<Mode, PolyIdx, std::index_sequence<Is...>>
    : public MultiBaseBranch<Is>... {
    static constexpr size_t kHeaderBytes = (sizeof(MultiBaseBranch<Is>) + ...);
    bench_core::PayloadStorage<Mode, kHeaderBytes> storage;

    explicit MultiDerived(int id) { storage.id = id; }

    NOINLINE int update(int v) override {
        return bench_core::compute_payload(v, storage.id, PolyIdx);
    }
};

template <FootprintMode Mode>
struct MultiHeapCase {
    using Handle = TargetMultiBase*;
    static constexpr size_t ObjectSize = sizeof(MultiDerived<Mode, 0>);

    template <size_t N>
    struct Maker { static Handle create(int id) { return new MultiDerived<Mode, N>(id); } };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static void destroy(Handle h) { delete h; }
    static int dispatch(Handle h, int val) { return h->update(val); }
};

// ============================================================================
// 02.3 Virtual Diamond Inheritance
// ============================================================================

struct VBase { virtual ~VBase() = default; virtual int update(int v) = 0; };
struct VLeft : virtual public VBase { int update(int v) override { return v; } };
struct VRight : virtual public VBase { int update(int v) override { return v; } };

struct DiamondProbePayload8 {
    int id = 0;
    char pad[4]{};
};

struct VDiamondProbe8 : public VLeft, public VRight {
    DiamondProbePayload8 storage;
    explicit VDiamondProbe8(int id) { storage.id = id; }
    NOINLINE int update(int v) override { return v; }
};

inline constexpr size_t kDiamondHeaderBytes = sizeof(VDiamondProbe8) - sizeof(DiamondProbePayload8);

template <FootprintMode Mode, size_t PolyIdx>
struct VDiamond : public VLeft, public VRight {
    bench_core::PayloadStorage<Mode, kDiamondHeaderBytes> storage;
    explicit VDiamond(int id) { storage.id = id; }

    NOINLINE int update(int v) override {
        return bench_core::compute_payload(v, storage.id, PolyIdx);
    }

    static void* operator new(size_t count) {
        return ::operator new(count, std::align_val_t{bench_core::target_alignment_v<Mode>});
    }

    static void operator delete(void* ptr) noexcept {
        ::operator delete(ptr, std::align_val_t{bench_core::target_alignment_v<Mode>});
    }
};

static_assert(sizeof(VDiamond<FootprintMode::Aligned64B, 0>) == 64, "Aligned64B VDiamond must be 64 bytes");
static_assert(sizeof(VDiamond<FootprintMode::Heavy256B, 0>) == 256, "Heavy256B VDiamond must be 256 bytes");

template <FootprintMode Mode>
struct DiamondHeapCase {
    using Handle = VBase*;
    static constexpr size_t ObjectSize = sizeof(VDiamond<Mode, 0>);

    template <size_t N>
    struct Maker { static Handle create(int id) { return new VDiamond<Mode, N>(id); } };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static void destroy(Handle h) { delete h; }
    static int dispatch(Handle h, int val) { return h->update(val); }
};

// ============================================================================
// 02.4 Fat Virtual Table (64 Virtual Methods)
// ============================================================================

template <size_t Slot> struct VSlot {};

template <size_t N>
struct FatBaseChain : public FatBaseChain<N - 1> {
    using FatBaseChain<N - 1>::call_slot;
    virtual int call_slot(VSlot<N>, int v) = 0;
};
template <>
struct FatBaseChain<0> {
    virtual ~FatBaseChain() = default;
    virtual int call_slot(VSlot<0>, int v) = 0;
};

using FatBaseRoot = FatBaseChain<cfg::FAT_VTBL_SIZE - 1>;

template <size_t N, typename DerivedT>
struct FatImplChain : public FatImplChain<N - 1, DerivedT> {
    using FatImplChain<N - 1, DerivedT>::call_slot;
    NOINLINE int call_slot(VSlot<N>, int v) override {
        return static_cast<DerivedT*>(this)->eval_slot(v, N);
    }
};
template <typename DerivedT>
struct FatImplChain<0, DerivedT> : public FatBaseRoot {
    using FatBaseRoot::call_slot;
    NOINLINE int call_slot(VSlot<0>, int v) override {
        return static_cast<DerivedT*>(this)->eval_slot(v, 0);
    }
};

template <FootprintMode Mode, size_t PolyIdx>
struct alignas(bench_core::target_alignment_v<Mode>) FatDerived : public FatImplChain<cfg::FAT_VTBL_SIZE - 1, FatDerived<Mode, PolyIdx>> {
    bench_core::PayloadStorage<Mode, sizeof(FatBaseRoot)> storage;
    explicit FatDerived(int id) { storage.id = id; }

    int eval_slot(int v, size_t slot) const {
        return bench_core::compute_payload(v + static_cast<int>(slot), storage.id, PolyIdx);
    }
};

static_assert(sizeof(FatDerived<FootprintMode::Aligned64B, 0>) == 64, "Aligned64B FatDerived must be 64 bytes");
static_assert(sizeof(FatDerived<FootprintMode::Heavy256B, 0>) == 256, "Heavy256B FatDerived must be 256 bytes");

template <FootprintMode Mode>
struct FatVTableHeapCase {
    using Handle = FatBaseRoot*;
    static constexpr size_t ObjectSize = sizeof(FatDerived<Mode, 0>);

    template <size_t N>
    struct Maker { static Handle create(int id) { return new FatDerived<Mode, N>(id); } };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static void destroy(Handle h) { delete h; }
    static int dispatch(Handle h, int val) {
        return h->call_slot(VSlot<cfg::FAT_VTBL_SIZE - 1>{}, val);
    }
};


REGISTER_HEAP_MATRIX(VirtualHeapCase,      "02 Virtual: Polymorphic");
REGISTER_HEAP_MATRIX(DeepHeapCase,         "02.1 Hierarchy: Deep Chain");
REGISTER_HEAP_MATRIX(MultiHeapCase,        "02.2 Hierarchy: Multi Inherit (Thunks)");
REGISTER_HEAP_MATRIX(DiamondHeapCase,      "02.3 Hierarchy: Virtual Diamond");
REGISTER_HEAP_MATRIX(FatVTableHeapCase,    "02.4 Hierarchy: Fat VTable (64 methods)");

} // namespace case_02_virtual