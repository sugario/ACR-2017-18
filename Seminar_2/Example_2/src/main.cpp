#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

#define KILOBYTE (1024U)
#define MEGABYTE (1024U * KILOBYTE)
#define ARR_LENGTH (64U * MEGABYTE)

#define INCREMENT (512U)

int32_t main() {
    Clock clock;
    auto *arr = new int32_t[ARR_LENGTH]();
    auto K = INCREMENT;

    clock.Start();
    for (auto i = 0U; i < ARR_LENGTH; i += K) {
        arr[i] *= 3;
    }
    INFO("Loop: %lld ms\n", clock.Elapsed());

    delete[] arr;

    return EXIT_SUCCESS;
}
