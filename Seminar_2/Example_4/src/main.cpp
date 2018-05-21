#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

#define BIT             (1U)
#define BYTE            (8U * BIT)
#define KILOBYTE        (1024U * BYTE)
#define MEGABYTE        (1024U * KILOBYTE)

#define ARR_LENGTH      (2U)

int32_t main() {
    Clock clock;

    const auto steps = 32U * MEGABYTE;
    auto *arr = new int32_t[ARR_LENGTH]();

    clock.Start();
    for (auto i = 0U; i < steps; i++) {
        arr[0U]++;
        arr[0U]++;
    }
    INFO("Elapsed time for loop_1: %lld ms\n", clock.ElapsedMiliSeconds());

    clock.Start();
    for (auto i = 0U; i < steps; i++) {
        arr[0U]++;
        arr[1U]++;
    }
    INFO("Elapsed time for loop_2: %lld ms\n", clock.ElapsedMiliSeconds());

    delete[] arr;

    return EXIT_SUCCESS;
}
