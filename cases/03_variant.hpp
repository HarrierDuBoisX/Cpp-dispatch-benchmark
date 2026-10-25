#pragma once

#include "../bench_core.hpp"

namespace case_03_variant {

using bench_core::FootprintMode;

template <FootprintMode Mode, size_t N>
struct VarAlternative {
    // Account for the 4-byte std::variant index + alignment padding
    bench_core::PayloadStorage<Mode, 4> storage;

    NOINLINE int update(int val) const {
        return bench_core::compute_payload(val, storage.id, N);
    }
};

template <FootprintMode Mode, size_t... Is>
auto make_variant_t(std::index_sequence<Is...>) -> std::variant<VarAlternative<Mode, Is>...>;

template <FootprintMode Mode>
using RawVariant = decltype(make_variant_t<Mode>(std::make_index_sequence<cfg::POLY_TYPES>{}));

template <FootprintMode Mode>
inline constexpr size_t variant_alignment_v =
    (Mode == FootprintMode::Aligned64B || Mode == FootprintMode::Heavy256B)
        ? 64
        : alignof(RawVariant<Mode>);

template <FootprintMode Mode>
struct alignas(variant_alignment_v<Mode>) AlignedVariantElement {
    RawVariant<Mode> value;
};

static_assert(sizeof(AlignedVariantElement<FootprintMode::Compact16B>) == 8, "Compact16B Variant must be 8 bytes");
static_assert(sizeof(AlignedVariantElement<FootprintMode::Unaligned60B>) == 60, "Unaligned60B Variant must be 60 bytes");
static_assert(sizeof(AlignedVariantElement<FootprintMode::Aligned64B>) == 64, "Aligned64B Variant must be 64 bytes");
static_assert(sizeof(AlignedVariantElement<FootprintMode::Heavy256B>) == 256, "Heavy256B Variant must be 256 bytes");

template <FootprintMode Mode>
struct VariantValueCase {
    using Element = AlignedVariantElement<Mode>;

    template <size_t N>
    struct Maker {
        static Element create(int id) {
            VarAlternative<Mode, N> alt{};
            alt.storage.id = id;
            return Element{ RawVariant<Mode>{alt} };
        }
    };

    static Element make(int id, size_t type_idx) {
        static constexpr auto table =
            bench_core::make_factory_table<Element, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return table[type_idx % cfg::POLY_TYPES](id);
    }

    static int dispatch(const Element& e, int val) {
        return std::visit([val](const auto& x) -> int {
            return x.update(val);
        }, e.value);
    }
};

REGISTER_VALUE_MATRIX(VariantValueCase, "03 Variant: std::visit");

} // namespace case_03_variant