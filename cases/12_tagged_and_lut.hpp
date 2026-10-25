#pragma once

#include "../bench_core.hpp"

namespace case_12_tagged_ptr {

using bench_core::FootprintMode;

template <FootprintMode Mode>
inline constexpr size_t fntable_value_alignment_v =
    (Mode == FootprintMode::Aligned64B || Mode == FootprintMode::Heavy256B) ? 64 : 4;

// ============================================================================
// 1. DIRECT FUNCTION TABLE (Array of pointers to functions without switch/default)
// ============================================================================
template <FootprintMode Mode>
struct alignas(fntable_value_alignment_v<Mode>) FnTableValueObj {
    std::uint8_t tag = 0;
    bench_core::PayloadStorage<Mode, 4> storage;

    template <size_t N>
    static NOINLINE int handler(const FnTableValueObj* self, int val) {
        return bench_core::compute_payload(val, self->storage.id, N);
    }

    template <size_t... Is>
    static constexpr auto make_table(std::index_sequence<Is...>) {
        using Fn = int (*)(const FnTableValueObj*, int);
        return std::array<Fn, sizeof...(Is)>{ &handler<Is>... };
    }
};

static_assert(sizeof(FnTableValueObj<FootprintMode::Compact16B>) == 8, "Compact16B FnTableValueObj must be 8 bytes");
static_assert(sizeof(FnTableValueObj<FootprintMode::Unaligned60B>) == 60, "Unaligned60B FnTableValueObj must be 60 bytes");
static_assert(sizeof(FnTableValueObj<FootprintMode::Aligned64B>) == 64, "Aligned64B FnTableValueObj must be 64 bytes");
static_assert(sizeof(FnTableValueObj<FootprintMode::Heavy256B>) == 256, "Heavy256B FnTableValueObj must be 256 bytes");

template <FootprintMode Mode>
struct DirectFnTableValueCase {
    using Element = FnTableValueObj<Mode>;

    static Element make(int id, size_t t) {
        Element e{};
        e.tag = static_cast<std::uint8_t>(t % cfg::POLY_TYPES);
        e.storage.id = id;
        return e;
    }

    static int dispatch(const Element& e, int val) {
        static constexpr auto table =
            Element::make_table(std::make_index_sequence<cfg::POLY_TYPES>{});
        return table[e.tag](&e, val);
    }
};


template <FootprintMode Mode>
struct alignas(bench_core::target_alignment_v<Mode>) RawHeapPayload {
    bench_core::PayloadStorage<Mode, 0> storage;

    template <size_t N>
    static NOINLINE int process(const RawHeapPayload* self, int val) {
        return bench_core::compute_payload(val, self->storage.id, N);
    }

    template <size_t... Is>
    static constexpr auto make_table(std::index_sequence<Is...>) {
        using Fn = int (*)(const RawHeapPayload*, int);
        return std::array<Fn, sizeof...(Is)>{ &process<Is>... };
    }
};

static_assert(sizeof(RawHeapPayload<FootprintMode::Aligned64B>) == 64, "Aligned64B RawHeapPayload must be 64 bytes");
static_assert(sizeof(RawHeapPayload<FootprintMode::Heavy256B>) == 256, "Heavy256B RawHeapPayload must be 256 bytes");

template <FootprintMode Mode>
struct TaggedPointerHeapCase {
    // Store exactly 8 bytes (uintptr_t) instead of a 16-byte fat pointer
    using Handle = std::uintptr_t;
    using ObjType = RawHeapPayload<Mode>;
    static constexpr size_t ObjectSize = sizeof(ObjType);

    static constexpr std::uintptr_t ADDR_MASK = 0x0000FFFFFFFFFFFFull;
    static constexpr unsigned int TAG_SHIFT = 48;

    static Handle create(int id, size_t type_idx) {
        auto* ptr = new ObjType{};
        ptr->storage.id = id;
        std::uintptr_t raw = reinterpret_cast<std::uintptr_t>(ptr);
        std::uintptr_t tag = (type_idx % cfg::POLY_TYPES) << TAG_SHIFT;
        return (raw & ADDR_MASK) | tag;
    }

    static void destroy(Handle h) {
        auto* ptr = reinterpret_cast<ObjType*>(h & ADDR_MASK);
        delete ptr;
    }

    static int dispatch(Handle h, int val) {
        static constexpr auto table =
            ObjType::make_table(std::make_index_sequence<cfg::POLY_TYPES>{});

        // Calculating the function's index does not depend on loading from the heap!
        const size_t tag = static_cast<size_t>(h >> TAG_SHIFT);
        const auto* ptr = reinterpret_cast<const ObjType*>(h & ADDR_MASK);
        return table[tag](ptr, val);
    }
};

REGISTER_VALUE_MATRIX(DirectFnTableValueCase, "12.1 Table: Direct FnPtr Array (No Switch)");
REGISTER_HEAP_MATRIX(TaggedPointerHeapCase,   "12.2 Pointers: 64-bit Tagged Pointer (48b Addr + 16b Tag)");

} // namespace case_12_tagged_ptr