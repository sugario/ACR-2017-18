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

#define INCREMENT       (512U)

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
