#include <Utility/Random.hpp>
#include <Utility/Traces.hpp>

#include <chrono>
#include <cstdint>
#include <cstdlib>

#define ARRAY_LENGTH        100000
#define ARRAY_MIN_RANGE     -1000
#define ARRAY_MAX_RANGE     1000

typedef std::chrono::high_resolution_clock Clock;

int32_t main()
{
    const Random random;
    int32_t array[ARRAY_LENGTH];

    auto result = 0;

    for (auto& num : array)
    {
        num = random.Next(ARRAY_MIN_RANGE, ARRAY_MAX_RANGE);
        DEBUG("[Main] Adding to array: %d\n", num);
    }

    const auto clockStart = Clock::now();
    for (const auto& num : array)
    {
        result += num;
    }
    const auto clockEnd = Clock::now();

    INFO("[Main] Execution time: %lld microsec\n",
        std::chrono::duration_cast<std::chrono::microseconds>
        (clockEnd - clockStart).count());
    INFO("[Main] Final result: %d\n", result);

    return EXIT_SUCCESS;
}
