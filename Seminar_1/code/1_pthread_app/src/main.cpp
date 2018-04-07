#include <Utility/Random.hpp>
#include <Utility/Traces.hpp>

#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cmath>

#define ARRAY_LENGTH        100000
#define ARRAY_MIN_RANGE     -1000
#define ARRAY_MAX_RANGE     1000

#define NUMBER_OF_THREADS   4

struct ArgStruct {
    int32_t threadId;
    int32_t *arrayStart;
    int32_t *arrayEnd;
    int32_t result;
};

typedef std::chrono::high_resolution_clock Clock;

void* GetPartialSum(void *arguments)
{
    auto *args = static_cast<struct ArgStruct *>(arguments);
    auto result = 0;

    DEBUG("[Thread %d] Started...\n", args->threadId);
    DEBUG("[Thread %d] Starting with %d\n", args->threadId, *args->arrayStart);
    DEBUG("[Thread %d] Ending with %d\n", args->threadId, *args->arrayEnd);

    while (args->arrayStart <= args->arrayEnd)
    {
        result += *args->arrayStart;
        args->arrayStart++;
    }

    args->result = result;

    DEBUG("[Thread %d] Calculated %d\n", args->threadId, result);

    return nullptr;
}

int32_t main()
{
    DEBUG("[Main] Starting program...\n");
    DEBUG("[Main] ARRAY_LENGTH: %d\n", ARRAY_LENGTH);
    DEBUG("[Main] NUMBER_OF_THREADS: %d\n", NUMBER_OF_THREADS);

    const Random random;
    struct ArgStruct args[NUMBER_OF_THREADS];
    pthread_t threads[NUMBER_OF_THREADS];
    int32_t array[ARRAY_LENGTH];

    auto result = 0;
    const auto range = static_cast<int>
        (static_cast<float>(ARRAY_LENGTH) / NUMBER_OF_THREADS);
    DEBUG("[Main] Division range: %d\n", range);

    DEBUG("[Main] Making random array...\n");
    for (auto& num : array)
    {
        num = random.Next(ARRAY_MIN_RANGE, ARRAY_MAX_RANGE);
        DEBUG("[Main] Adding to array: %d\n", num);
    }

    const auto clockStart = Clock::now();
    for (auto id = 0; id < NUMBER_OF_THREADS; id++)
    {
        args[id].threadId = id;
        args[id].arrayStart = array + id * range;
        args[id].arrayEnd = array + (id + 1) * range - 1;
        if (id == NUMBER_OF_THREADS - 1)
        {
            args[id].arrayEnd = &array[ARRAY_LENGTH - 1];
        }

        const auto rc = pthread_create(&threads[id],
                                       nullptr,
                                       GetPartialSum,
                                       &args[id]);
        if (rc)
        {
            INFO("[Main] ERROR; return code from pthread_create() is %d\n", rc);
            return EXIT_FAILURE;
        }
    }

    DEBUG("[Main] Joining threads!\n");
    for (const auto& t : threads)
    {
        pthread_join(t, nullptr);
    }

    DEBUG("[Main] Calculating result!\n");
    for (const auto& arg : args)
    {
        result += arg.result;
    }

    const auto clockEnd = Clock::now();

    INFO("[Main] Execution time: %lld microsec\n",
         std::chrono::duration_cast<std::chrono::microseconds>
                (clockEnd - clockStart).count());
    INFO("[Main] Final result: %d\n", result);

    return EXIT_SUCCESS;
}
