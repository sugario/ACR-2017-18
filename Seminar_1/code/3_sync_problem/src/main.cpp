#include <Utility/Traces.hpp>

#include <mutex>
#include <thread>

#include <cstdint>
#include <vector>

#define NUM_OF_ITERATIONS   1000U
#define NUM_OF_THREADS      60U

void Increment(uint32_t &n, std::mutex &mutex)
{
    for (auto i = 0U; i < NUM_OF_ITERATIONS; ++i)
    {
        mutex.lock();
        n++;
        mutex.unlock();
    }
}

int32_t main()
{
    auto val = 0U;

    std::vector<std::thread> threads;
    std::mutex mutex;

    for (auto i = 0U; i < NUM_OF_THREADS; i++)
    {
        threads.emplace_back(std::thread(Increment,
                             std::ref(val),
                             std::ref(mutex)));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    INFO("%u\n", val);

    return EXIT_SUCCESS;
}
