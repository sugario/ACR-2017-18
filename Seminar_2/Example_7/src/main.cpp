#include <Utility/Clock.hpp>
#include <Utility/Traces.hpp>

#include <cstdint>
#include <cstdlib>

uint32_t A = 0;
uint32_t B = 0;
uint32_t C = 0;
uint32_t D = 0;
uint32_t E = 0;
uint32_t F = 0;
uint32_t G = 0;

static void WeirdnessABCD() noexcept {
    for (auto i = 0U; i < 200000000U; i++) {
        A++;
        B++;
        C++;
        D++;
    }
}

static void WeirdnessACEG() noexcept {
    for (auto i = 0U; i < 200000000U; i++) {
        A++;
        C++;
        E++;
        G++;
    }
}

static void WeirdnessAC() noexcept {
    for (auto i = 0U; i < 200000000U; i++) {
        A++;
        C++;
    }
}

int32_t main() noexcept {
    Clock clock;

    clock.Start();
    WeirdnessABCD();
    auto elapsedTimeMS = clock.ElapsedMiliSeconds();
    INFO("A++; B++; C++; D++;\t\t%lld ms\n", elapsedTimeMS);

    clock.Start();
    WeirdnessACEG();
    elapsedTimeMS = clock.ElapsedMiliSeconds();
    INFO("A++; C++; E++; G++;\t\t%lld ms\n", elapsedTimeMS);

    clock.Start();
    WeirdnessAC();
    elapsedTimeMS = clock.ElapsedMiliSeconds();
    INFO("A++; C++;\t\t\t%lld ms\n", elapsedTimeMS);

    return EXIT_SUCCESS;
}
