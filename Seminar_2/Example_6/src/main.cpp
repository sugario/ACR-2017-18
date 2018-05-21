#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

#include <thread>
#include <vector>

#define BIT             (1U)
#define BYTE            (8U * BIT)
#define KILOBYTE        (1024U * BYTE)
#define MEGABYTE        (1024U * KILOBYTE)

#define ARR_MEMORY_SIZE (256U * MEGABYTE)
#define ARR_LENGTH      (ARR_MEMORY_SIZE / (sizeof(int32_t) * BYTE))

#define NUM_OF_THREADS  (4U)

auto *s_counter = new int32_t[ARR_LENGTH]();

static void UpdateCounter(const uint32_t position) noexcept {
    for (auto j = 0U; j < 100000000U; j++) {
        s_counter[position] = s_counter[position] + 3;
    }
}

int32_t main() {
    Clock clock;

    const uint32_t positions1[] = { 0, 1, 2, 3 };
    const uint32_t positions2[] = { 16, 32, 48, 64 };

    std::vector<std::thread> threads;
    threads.reserve(NUM_OF_THREADS);

    clock.Start();
    for (auto i = 0U; i < NUM_OF_THREADS; i++) {
        threads.emplace_back(std::thread(UpdateCounter, positions1[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }
    INFO("Positions_1 took %.2f seconds\n", clock.ElapsedMiliSeconds() / 1000.0);

    threads.clear();
    clock.Start();
    for (auto i = 0U; i < NUM_OF_THREADS; i++) {
        threads.emplace_back(std::thread(UpdateCounter, positions2[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }
    INFO("Positions_2 took %.2f seconds\n", clock.ElapsedMiliSeconds() / 1000.0);

    return EXIT_SUCCESS;
}
