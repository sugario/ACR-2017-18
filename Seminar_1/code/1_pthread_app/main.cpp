#define HAVE_STRUCT_TIMESPEC    // timespec issues
#include <pthread.h>
#include <iostream>

#define NUM_THREADS	2

void* PrintHello(void* threadId) noexcept
{
    const auto tId = (long)threadId;
    printf("Hello World! It's me, thread #%ld!\n", tId);

    pthread_exit(nullptr);
    return nullptr;
}

int32_t main(void) noexcept
{
    pthread_t threads[NUM_THREADS];

    for (long t = 0; t < NUM_THREADS; t++)
    {
        printf("In main: creating thread %ld\n", t);
        const auto rc = pthread_create(&threads[t], nullptr, PrintHello, (void*)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            return EXIT_FAILURE;
        }
    }
    
    pthread_exit(nullptr);
    return EXIT_SUCCESS;
}
