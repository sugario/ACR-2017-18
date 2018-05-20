#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

#define BIT             (1U)
#define BYTE            (8U * BIT)
#define KILOBYTE        (1024U * BYTE)
#define MEGABYTE        (1024U * KILOBYTE)

#define ARR_MEMORY_SIZE (256U * MEGABYTE)
#define ARR_LENGTH      (ARR_MEMORY_SIZE / (sizeof(int32_t) * BYTE))

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
