#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

#define BIT             (1U)
#define BYTE            (8U * BIT)
#define KILOBYTE        (1024U * BYTE)
#define MEGABYTE        (1024U * KILOBYTE)

#define L3_CACHE_SIZE   (9U * MEGABYTE)
#define ARR_LENGTH        (32U * KILOBYTE)

int32_t main() {
    Clock clock;

    const auto steps = L3_CACHE_SIZE;
    auto *arr = new int32_t[ARR_LENGTH]();

    INFO("Array size: %u\n", ARR_LENGTH);
    clock.Start();
    for (auto i = 0U; i < steps; i++) {
        arr[(i * 16) % ARR_LENGTH]++;
    }

    int64_t elapsedNS = clock.ElapsedNanoSeconds();
    INFO("Time per element: %lld ns\n", elapsedNS / ARR_LENGTH);

    delete[] arr;

    return EXIT_SUCCESS;
}
