#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

#define BIT             (1U)
#define BYTE            (8U * BIT)
#define KILOBYTE        (1024U * BYTE)
#define MEGABYTE        (1024U * KILOBYTE)

#define ARR_MEMORY_SIZE (10U * MEGABYTE)
#define ARR_LENGTH      (ARR_MEMORY_SIZE / (sizeof(int32_t) * BYTE))

int32_t main() {
    Clock clock;

    const auto steps = 64U * 1024U * 1024U;
    auto *arr = new int32_t[ARR_LENGTH]();

    INFO("Array size: %u\n", ARR_LENGTH);
    for (auto i = 0U; i < steps; i++) {
        clock.Start();
        arr[(i * 16) % ARR_LENGTH]++;
        const auto elapsedNS = clock.ElapsedNanoSeconds();
        INFO("Time per element: %lld ns\n", elapsedNS);
    }


    delete[] arr;

    return EXIT_SUCCESS;
}
