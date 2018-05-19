#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

#define BIT             (1U)
#define BYTE            (8U * BIT)
#define KILOBYTE        (1024U * BYTE)
#define MEGABYTE        (1024U * KILOBYTE)

#define L3_CACHE_SIZE   (9U * MEGABYTE)
#define ARR_LENGTH      (L3_CACHE_SIZE)

int32_t main() {
    Clock clock;
    auto *arr = new int32_t[ARR_LENGTH]();

    clock.Start();
    for (auto i = 0U; i < ARR_LENGTH; i++) {
        arr[i] *= 3;
    }
    INFO("Loop_1: %lld ms\n", clock.ElapsedMiliSeconds());

    clock.Start();
    for (auto i = 0U; i < ARR_LENGTH; i += 16) {
        arr[i] *= 3;
    }
    INFO("Loop_2: %lld ms\n", clock.ElapsedMiliSeconds());

    delete[] arr;

    return EXIT_SUCCESS;
}
