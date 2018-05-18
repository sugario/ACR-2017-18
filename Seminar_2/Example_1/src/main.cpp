#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

#define KILOBYTE (1024U)
#define MEGABYTE (1024U * KILOBYTE)
#define ARR_LENGTH (64U * MEGABYTE)

int32_t main() {
    Clock clock;
    auto *arr = new int32_t[ARR_LENGTH]();

    clock.Start();
    for (auto i = 0U; i < ARR_LENGTH; i++) {
        arr[i] *= 3;
    }
    INFO("Loop_1: %lld ms\n", clock.Elapsed());

    clock.Start();
    for (auto i = 0U; i < ARR_LENGTH; i += 16) {
        arr[i] *= 3;
    }
    INFO("Loop_2: %lld ms\n", clock.Elapsed());

    delete[] arr;

    return EXIT_SUCCESS;
}
