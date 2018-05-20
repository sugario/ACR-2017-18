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

#define INCREMENT       (1024U)

int32_t main() {
    Clock clock;
    auto *arr = new int32_t[ARR_LENGTH]();
    const auto K = INCREMENT;

    clock.Start();
    for (auto i = 0U; i < ARR_LENGTH; i += K) {
        arr[i] *= 3;
    }
    INFO("Loop: %lld ms\n", clock.ElapsedMiliSeconds());

    delete[] arr;

    return EXIT_SUCCESS;
}
