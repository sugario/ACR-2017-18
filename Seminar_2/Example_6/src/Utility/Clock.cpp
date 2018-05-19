#include "Utility/Clock.hpp"

Clock::Clock() noexcept {
    this->Start();
}

void Clock::Start() noexcept {
    StartTime = std::chrono::system_clock::now();
}

int64_t Clock::ElapsedMiliSeconds() const noexcept {
    const auto CurrentTime = std::chrono::system_clock::now();
    const std::chrono::duration<double> elapsed_seconds = CurrentTime - StartTime;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count();
}

int64_t Clock::ElapsedNanoSeconds() const noexcept {
    const auto CurrentTime = std::chrono::system_clock::now();
    const std::chrono::duration<double> elapsed_seconds = CurrentTime - StartTime;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count();
}
