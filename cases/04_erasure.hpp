#pragma once

#include "../bench_core.hpp"

namespace case_04_erasure {

using bench_core::FootprintMode;

template <FootprintMode Mode>
struct alignas(bench_core::target_alignment_v<Mode>) ErasedStruct {
    bench_core::PayloadStorage<Mode, 0> storage;
};

static_assert(sizeof(ErasedStruct<FootprintMode::Aligned64B>) == 64, "Aligned64B ErasedStruct must be 64 bytes");
static_assert(sizeof(ErasedStruct<FootprintMode::Heavy256B>) == 256, "Heavy256B ErasedStruct must be 256 bytes");

struct FPVTable {
    int (*update)(const void* self, int val);
    void (*drop)(void* self);
};

struct FPTraitObject {
    void* self;
    const FPVTable* vtable;

    inline int update(int val) const {
        return vtable->update(self, val);
    }
};

template <FootprintMode Mode, size_t N>
struct FPTraitImpl {
    static NOINLINE int upd(const void* s, int v) {
        auto* obj = static_cast<const ErasedStruct<Mode>*>(s);
        return bench_core::compute_payload(v, obj->storage.id, N);
    }
    static void del(void* s) {
        delete static_cast<ErasedStruct<Mode>*>(s);
    }
    static constexpr FPVTable vtable = { &upd, &del };
};

template <FootprintMode Mode>
struct FPFatPtrHeapCase {
    using Handle = FPTraitObject;
    static constexpr size_t ObjectSize = sizeof(ErasedStruct<Mode>);

    template <size_t N>
    struct Maker {
        static Handle create(int id) {
            auto* obj = new ErasedStruct<Mode>{};
            obj->storage.id = id;
            return FPTraitObject{ obj, &FPTraitImpl<Mode, N>::vtable };
        }
    };

    static Handle create(int id, size_t type_idx) {
        static constexpr auto table =
            bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return table[type_idx % cfg::POLY_TYPES](id);
    }

    static void destroy(Handle h) { h.vtable->drop(h.self); }
    static int dispatch(const Handle& h, int val) { return h.update(val); }
};

// C-Style: pair { pointer to structure, pointer to function }
template <FootprintMode Mode>
struct CFuncPtrHeapCase {
    using CFunc = int (*)(const void*, int);
    using Handle = std::pair<ErasedStruct<Mode>*, CFunc>;
    static constexpr size_t ObjectSize = sizeof(ErasedStruct<Mode>);

    template <size_t N>
    struct Maker {
        static NOINLINE int call(const void* self, int val) {
            auto* obj = static_cast<const ErasedStruct<Mode>*>(self);
            return bench_core::compute_payload(val, obj->storage.id, N);
        }
        static Handle create(int id) {
            auto* obj = new ErasedStruct<Mode>{};
            obj->storage.id = id;
            return { obj, &call };
        }
    };

    static Handle create(int id, size_t type_idx) {
        static constexpr auto table =
            bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return table[type_idx % cfg::POLY_TYPES](id);
    }

    static void destroy(Handle h) { delete h.first; }
    static int dispatch(const Handle& h, int val) { return h.second(h.first, val); }
};

REGISTER_HEAP_MATRIX(FPFatPtrHeapCase, "04 Erasure: Fat Ptr (Trait Object)");
REGISTER_HEAP_MATRIX(CFuncPtrHeapCase, "04.1 Erasure: C Struct* + FuncPtr");

} // namespace case_04_erasure