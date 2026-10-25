#pragma once

#include "../bench_core.hpp"

namespace case_07_wrappers {

using bench_core::FootprintMode;

// 1. FuncRef (2 pointers: void* obj + callback function = 16 bytes)
template <FootprintMode Mode, size_t N>
struct alignas(bench_core::target_alignment_v<Mode>) FuncRefTarget {
    bench_core::PayloadStorage<Mode, 0> storage;
    NOINLINE int update(int v) const { return bench_core::compute_payload<N>(v, storage.id); }
};

static_assert(sizeof(FuncRefTarget<FootprintMode::Aligned64B, 0>) == 64, "Aligned64B FuncRefTarget must be 64 bytes");
static_assert(sizeof(FuncRefTarget<FootprintMode::Heavy256B, 0>) == 256, "Heavy256B FuncRefTarget must be 256 bytes");

struct FuncRefHandle {
    void* obj;
    int (*func)(const void*, int);

    inline int update(int v) const { return func(obj, v); }
};

static_assert(sizeof(FuncRefHandle) == 2 * sizeof(void*), "FuncRefHandle must be exactly 2 pointers (16 bytes)");

template <FootprintMode Mode>
struct FuncRefHeapCase {
    using Handle = FuncRefHandle;
    static constexpr size_t ObjectSize = sizeof(FuncRefTarget<Mode, 0>);

    template <size_t N>
    struct Maker {
        static Handle create(int id) {
            auto* ptr = new FuncRefTarget<Mode, N>{};
            ptr->storage.id = id;
            return FuncRefHandle{
                ptr,
                +[](const void* p, int v) -> int { return static_cast<const FuncRefTarget<Mode, N>*>(p)->update(v); }
            };
        }
    };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static void destroy(Handle h) {
        delete static_cast<FuncRefTarget<Mode, 0>*>(h.obj);
    }
    static int dispatch(const Handle& h, int val) { return h.update(val); }
};

// 2. SBO Type Erasure (Small Buffer Optimization without heap allocation)
template <FootprintMode Mode>
struct alignas(bench_core::target_alignment_v<Mode>) SBO_Object {
    using Invoker = int (*)(const void*, int);
    Invoker invoke = nullptr;
    bench_core::PayloadStorage<Mode, sizeof(Invoker)> storage;

    template <size_t N>
    static NOINLINE int invoke_impl(const void* ptr, int v) {
        auto* self = static_cast<const bench_core::PayloadStorage<Mode, sizeof(Invoker)>*>(ptr);
        return bench_core::compute_payload<N>(v, self->id);
    }

    template <size_t N>
    static SBO_Object create_for(int id) {
        SBO_Object sbo{};
        sbo.storage.id = id;
        sbo.invoke = &invoke_impl<N>;
        return sbo;
    }

    inline int update(int v) const { return invoke(&storage, v); }
};

#pragma pack(push, 4)
template <>
struct SBO_Object<FootprintMode::Unaligned60B> {
    using Invoker = int (*)(const void*, int);
    Invoker invoke = nullptr;
    bench_core::PayloadStorage<FootprintMode::Unaligned60B, sizeof(Invoker)> storage;

    template <size_t N>
    static NOINLINE int invoke_impl(const void* ptr, int v) {
        auto* self = static_cast<const bench_core::PayloadStorage<FootprintMode::Unaligned60B, sizeof(Invoker)>*>(ptr);
        return bench_core::compute_payload<N>(v, self->id);
    }

    template <size_t N>
    static SBO_Object create_for(int id) {
        SBO_Object sbo{};
        sbo.storage.id = id;
        sbo.invoke = &invoke_impl<N>;
        return sbo;
    }

    inline int update(int v) const { return invoke(&storage, v); }
};
#pragma pack(pop)

static_assert(sizeof(SBO_Object<FootprintMode::Compact16B>) == 16, "Compact16B SBO_Object must be 16 bytes");
static_assert(sizeof(SBO_Object<FootprintMode::Unaligned60B>) == 60, "Unaligned60B SBO_Object must be 60 bytes");
static_assert(sizeof(SBO_Object<FootprintMode::Aligned64B>) == 64, "Aligned64B SBO_Object must be 64 bytes");
static_assert(sizeof(SBO_Object<FootprintMode::Heavy256B>) == 256, "Heavy256B SBO_Object must be 256 bytes");

template <FootprintMode Mode>
struct SBOCase {
    using Element = SBO_Object<Mode>;
    template <size_t N>
    struct Maker { static Element create(int id) { return Element::template create_for<N>(id); } };

    static Element make(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Element, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static int dispatch(const Element& e, int val) { return e.update(val); }
};

// 3.1 std::function In-Place SBO (Guaranteed 4-byte capture, zero hidden heap allocations)
template <size_t N>
struct StdFuncSboCallable {
    int id = 0;

    NOINLINE int operator()(int v) const {
        return bench_core::compute_payload<N>(v, id);
    }
};

template <FootprintMode Mode>
struct StdFunctionInPlaceSBOCase {
    using Element = std::function<int(int)>;

    template <size_t N>
    struct Maker {
        static Element create(int id) {
            return Element{ StdFuncSboCallable<N>{id} };
        }
    };

    static Element make(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Element, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static int dispatch(const Element& f, int val) { return f(val); }
};

// 3.2 std::function Payload-Scaled (Triggers hidden heap allocation when Mode > SBO threshold)
template <FootprintMode Mode, size_t N>
struct StdFuncCallable {
    bench_core::PayloadStorage<Mode, 0> data{};

    NOINLINE int operator()(int v) const {
        return bench_core::compute_payload<N>(v, data.id);
    }
};

template <FootprintMode Mode>
struct StdFunctionCase {
    using Element = std::function<int(int)>;

    template <size_t N>
    struct Maker {
        static Element create(int id) {
            StdFuncCallable<Mode, N> callable{};
            callable.data.id = id;
            return Element{ callable };
        }
    };

    static Element make(int id, size_t t) {
        static constexpr auto tbl = bench_core::make_factory_table<Element, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }
    static int dispatch(const Element& f, int val) { return f(val); }
};

REGISTER_VALUE_MATRIX(StdFunctionInPlaceSBOCase, "07.1 Wrappers: std::function (In-Place SBO)");
REGISTER_VALUE_MATRIX(StdFunctionCase,           "07.2 Wrappers: std::function (Payload-Scaled)");
REGISTER_HEAP_MATRIX(FuncRefHeapCase,            "07.3 Wrappers: FuncRef (2-ptr)");
REGISTER_VALUE_MATRIX(SBOCase,                   "07.4 Wrappers: SBO Type Erasure");

} // namespace case_07_wrappers