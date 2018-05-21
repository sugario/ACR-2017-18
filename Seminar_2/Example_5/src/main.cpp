#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

#define BIT             (1U)
#define BYTE            (8U * BIT)
#define KILOBYTE        (1024U * BYTE)
#define MEGABYTE        (1024U * KILOBYTE)

#define ARR_MEMORY_SIZE (24U * MEGABYTE)
#define ARR_LENGTH      (ARR_MEMORY_SIZE / (sizeof(int32_t) * BYTE))

#define MAX_STEP        (576U)

typedef uint8_t byte;

int64_t UpdateEveryKthByte(byte *arr, const uint32_t K) noexcept {
    Clock clock;
    clock.Start();

    const auto rep = MEGABYTE / BYTE;
    auto p = 0U;

    if (!arr) {
        return INT64_MAX;
    }

    for (auto i = 0U; i < rep; i++) {
        arr[p]++;
        p += K;
        if (p >= ARR_LENGTH) {
            p = 0U;
        }
    }

    return clock.ElapsedMiliSeconds();
}

int32_t main() {
    auto *arr = new byte[ARR_LENGTH]();

    for (auto step = 0U; step < MAX_STEP; step++) {
        const auto elapsedMiliSeconds = UpdateEveryKthByte(arr, step);
        INFO("Step:%u\tTime: %lld ms\n", step, elapsedMiliSeconds);
    }

    delete[] arr;

    return EXIT_SUCCESS;
}
