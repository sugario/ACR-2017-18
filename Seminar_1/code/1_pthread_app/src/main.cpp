#include <Utility/Random.hpp>
#include <Utility/Traces.hpp>

#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

#include <cstdint>
#include <cstdlib>
#include <cmath>

#define ARRAY_LENGTH    8
#define ARRAY_MIN_RANGE -1000
#define ARRAY_MAX_RANGE 1000

#define NUMBER_OF_THREADS 2

struct ArgStruct {
    int32_t threadId;
    int32_t *arrayStart;
    int32_t *arrayEnd;
    int32_t result;
};

void* GetPartialSum(void* arguments)
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
    INFO("[Main] Starting program...\n");
    DEBUG("[Main] ARRAY_LENGTH: %d\n", ARRAY_LENGTH);
    DEBUG("[Main] NUMBER_OF_THREADS: %d\n", NUMBER_OF_THREADS);

    Random random;
    struct ArgStruct args[NUMBER_OF_THREADS];
    pthread_t threads[NUMBER_OF_THREADS];
    int32_t array[ARRAY_LENGTH];

    auto result = 0;
    const auto range = static_cast<int>(std::round(static_cast<float>(ARRAY_LENGTH) / NUMBER_OF_THREADS));
    DEBUG("[Main] Division range: %d\n", range);

    INFO("[Main] Making random array...\n");
    for (auto i = 0; i < ARRAY_LENGTH; i++)
    {
        array[i] = random.Next(ARRAY_MIN_RANGE, ARRAY_MAX_RANGE);
        DEBUG("[Main] array[%u] = %d\n", i, array[i]);
    }

    for (auto id = 0; id < NUMBER_OF_THREADS; id++)
    {
        args[id].threadId = id;
        args[id].arrayStart = array + id * range;
        args[id].arrayEnd = array + (id + 1) * range - 1;
        if (args[id].arrayEnd > &array[ARRAY_LENGTH - 1])
        {
            args[id].arrayEnd = &array[ARRAY_LENGTH - 1];
        }

        const auto rc = pthread_create(&threads[id], nullptr, GetPartialSum, static_cast<void *>(&args[id]));
        if (rc)
        {
            INFO("[Main] ERROR; return code from pthread_create() is %d\n", rc);
            return EXIT_FAILURE;
        }
    }

    DEBUG("[Main] Joining threads!\n");
    for (auto& t : threads)
    {
        pthread_join(t, nullptr);
    }

    DEBUG("[Main] Calculating result!\n");
    for (auto& arg : args)
    {
        result += arg.result;
    }

    INFO("[Main] Final result: %d\n", result);

    return EXIT_SUCCESS;
}
