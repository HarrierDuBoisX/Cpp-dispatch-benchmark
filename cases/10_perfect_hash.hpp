#pragma once

#include "../bench_core.hpp"

namespace case_10_perfect_hash {

using bench_core::FootprintMode;

template <FootprintMode Mode>
inline constexpr size_t packet_value_alignment_v =
    (Mode == FootprintMode::Aligned64B || Mode == FootprintMode::Heavy256B) ? 64 : 4;

template <typename FuncT = int (*)(int, int), typename KeyT = int, std::size_t MaxCapacity = 64>
struct DispatchBuilder {
    std::array<KeyT, MaxCapacity> keys{};
    std::array<FuncT, MaxCapacity> handlers{};
    std::size_t count = 0;

    constexpr DispatchBuilder() = default;

    [[nodiscard]] constexpr DispatchBuilder add(KeyT key, FuncT h) const {
        DispatchBuilder result = *this;
        if (result.count < MaxCapacity) {
            result.keys[result.count] = key;
            result.handlers[result.count] = h;
            result.count++;
        }
        return result;
    }
};

template <auto BuilderData, auto DefaultHandler>
class FastDispatcher {
private:
    static constexpr std::size_t m_count = BuilderData.count;
    using KeyT = int;
    using FuncT = decltype(DefaultHandler);
    static constexpr KeyT INVALID_KEY = -1;

    static constexpr std::size_t m_table_size = []() constexpr {
        std::size_t n = (m_count <= 1) ? 2 : m_count * 16;
        std::size_t p = 1;
        while (p < n) p <<= 1;
        return p;
    }();

    static constexpr std::size_t m_shift = []() constexpr {
        std::size_t n = m_table_size;
        std::size_t p = 0;
        while (n > 1) { n >>= 1; p++; }
        return 32 - p;
    }();

    static constexpr std::uint32_t find_magic() {
        if (m_count <= 1) return 1;
        std::uint32_t magic = 0x9E3779B1;
        while (true) {
            bool collision = false;
            std::array<bool, m_table_size> used{};
            for (std::size_t i = 0; i < m_count; ++i) {
                std::uint32_t k = static_cast<std::uint32_t>(BuilderData.keys[i]);
                k ^= k >> 16;
                std::size_t idx = (k * magic) >> m_shift;
                if (used[idx]) { collision = true; break; }
                used[idx] = true;
            }
            if (!collision) return magic;
            magic = magic * 1664525 + 1013904223;
            magic |= 1;
        }
    }

    static constexpr std::uint32_t MAGIC = find_magic();

    struct alignas(64) OptimizedTable {
        std::array<KeyT, m_table_size> keys{};
        std::array<FuncT, m_table_size> handlers{};
    };

    static constexpr OptimizedTable build_table() {
        OptimizedTable table{};
        for (std::size_t i = 0; i < m_table_size; ++i) {
            table.keys[i] = INVALID_KEY;
            table.handlers[i] = static_cast<FuncT>(DefaultHandler);
        }
        for (std::size_t i = 0; i < m_count; ++i) {
            std::uint32_t k = static_cast<std::uint32_t>(BuilderData.keys[i]);
            k ^= k >> 16;
            std::size_t idx = (k * MAGIC) >> m_shift;
            table.keys[idx] = BuilderData.keys[i];
            table.handlers[idx] = BuilderData.handlers[i];
        }
        return table;
    }

    static constexpr OptimizedTable m_table = build_table();

public:
    template <typename... Args>
    static inline decltype(auto) dispatch(KeyT key, Args&&... args) {
        std::uint32_t k = static_cast<std::uint32_t>(key);
        k ^= k >> 16;
        const std::size_t idx = (k * MAGIC) >> m_shift;
        const bool is_valid = (m_table.keys[idx] == key);
        return (is_valid ? m_table.handlers[idx] : static_cast<FuncT>(DefaultHandler))(std::forward<Args>(args)...);
    }
};

template <size_t N>
NOINLINE int phash_handler(int val, int id) { return bench_core::compute_payload(val, id, N); }
NOINLINE int phash_miss(int, int) { return 0; }

template <size_t... Is>
constexpr auto build_phash_table(std::index_sequence<Is...>) {
    DispatchBuilder<int (*)(int, int), int> b{};
    ((b = b.add(static_cast<int>(Is), &phash_handler<Is>)), ...);
    return b;
}

constexpr auto phash_table = build_phash_table(std::make_index_sequence<cfg::POLY_TYPES>{});
using PHashDispatcher = FastDispatcher<phash_table, &phash_miss>;

template <size_t... Is>
std::unordered_map<int, int (*)(int, int)> build_stl_map(std::index_sequence<Is...>) {
    std::unordered_map<int, int (*)(int, int)> m;
    ((m[static_cast<int>(Is)] = &phash_handler<Is>), ...);
    return m;
}

template <FootprintMode Mode>
struct alignas(packet_value_alignment_v<Mode>) KeyedPacket {
    int key = 0;
    bench_core::PayloadStorage<Mode, 4> storage;
};

static_assert(sizeof(KeyedPacket<FootprintMode::Compact16B>) == 8, "Compact16B KeyedPacket must be 8 bytes");
static_assert(sizeof(KeyedPacket<FootprintMode::Unaligned60B>) == 60, "Unaligned60B KeyedPacket must be 60 bytes");
static_assert(sizeof(KeyedPacket<FootprintMode::Aligned64B>) == 64, "Aligned64B KeyedPacket must be 64 bytes");
static_assert(sizeof(KeyedPacket<FootprintMode::Heavy256B>) == 256, "Heavy256B KeyedPacket must be 256 bytes");

template <FootprintMode Mode>
struct StlUnorderedMapCase {
    using Element = KeyedPacket<Mode>;

    static Element make(int id, size_t t) {
        Element e{};
        e.key = static_cast<int>(t % cfg::POLY_TYPES);
        e.storage.id = id;
        return e;
    }

    static int dispatch(const Element& e, int val) {
        static const auto stl_map = build_stl_map(std::make_index_sequence<cfg::POLY_TYPES>{});
        auto it = stl_map.find(e.key);
        if (it != stl_map.end()) return it->second(val, e.storage.id);
        return phash_miss(val, e.storage.id);
    }
};

template <FootprintMode Mode>
struct PerfectHashCase {
    using Element = KeyedPacket<Mode>;

    static Element make(int id, size_t t) {
        Element e{};
        e.key = static_cast<int>(t % cfg::POLY_TYPES);
        e.storage.id = id;
        return e;
    }

    static int dispatch(const Element& e, int val) {
        return PHashDispatcher::dispatch(e.key, val, e.storage.id);
    }
};

REGISTER_VALUE_MATRIX(StlUnorderedMapCase, "10.1 Hash: std::unordered_map");
REGISTER_VALUE_MATRIX(PerfectHashCase,     "10.2 Hash: Compile-Time Perfect Hash");

} // namespace case_10_perfect_hash