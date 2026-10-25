#pragma once

#include "../bench_core.hpp"
#include <coroutine>
#include <new>

namespace case_14_coroutines {

using bench_core::FootprintMode;


inline constexpr size_t kCoroFrameHeaderEstimate = 4 * sizeof(void*);

template <FootprintMode Mode>
struct FrameRunnerTask {
    struct alignas(bench_core::target_alignment_v<Mode>) promise_type {
        int arg = 1;
        int result = 0;
        bench_core::PayloadStorage<Mode, kCoroFrameHeaderEstimate> storage{};

        FrameRunnerTask get_return_object() noexcept {
            return FrameRunnerTask{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() noexcept {}
        void unhandled_exception() noexcept {}

        struct StepAwaiter {
            promise_type& p;
            bool await_ready() const noexcept { return false; }
            void await_suspend(std::coroutine_handle<>) const noexcept {}
            int await_resume() const noexcept { return p.arg; }
        };

        StepAwaiter yield_value(int res) noexcept {
            result = res;
            return StepAwaiter{*this};
        }

        static void* operator new(size_t size) {
            return ::operator new(size, std::align_val_t{bench_core::target_alignment_v<Mode>});
        }

        static void operator delete(void* ptr, size_t size) noexcept {
            ::operator delete(ptr, size, std::align_val_t{bench_core::target_alignment_v<Mode>});
        }
    };

    std::coroutine_handle<promise_type> handle;
};

template <FootprintMode Mode, size_t N>
FrameRunnerTask<Mode> create_actor_coro(int id) {
    int v = 1;
    for (;;) {
        v = co_yield bench_core::compute_payload(v, id, N);
    }
}

template <FootprintMode Mode>
struct CoroutineHeapCase {
    using Promise = typename FrameRunnerTask<Mode>::promise_type;
    using Handle = std::coroutine_handle<Promise>;
    static constexpr size_t ObjectSize = sizeof(Promise);

    template <size_t N>
    struct Maker {
        static Handle create(int id) {
            FrameRunnerTask<Mode> task = create_actor_coro<Mode, N>(id);
            task.handle.promise().storage.id = id;
            // Advance from initial_suspend to the steady-state co_yield point
            task.handle.resume();
            return task.handle;
        }
    };

    static Handle create(int id, size_t t) {
        static constexpr auto tbl =
            bench_core::make_factory_table<Handle, Maker>(std::make_index_sequence<cfg::POLY_TYPES>{});
        return tbl[t % cfg::POLY_TYPES](id);
    }

    static void destroy(Handle& h) {
        if (h) h.destroy();
    }

    static int dispatch(const Handle& h, int val) {
        auto& p = h.promise();
        p.arg = val;
        h.resume();
        return p.result;
    }
};

REGISTER_HEAP_MATRIX(CoroutineHeapCase, "14.1 C++20 Coroutine: coroutine_handle::resume()");

} // namespace case_14_coroutines