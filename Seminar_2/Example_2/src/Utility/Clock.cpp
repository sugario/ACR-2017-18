#include "Utility/Clock.hpp"

Clock::Clock() {
    this->Start();
}

void Clock::Start() {
    StartTime = std::chrono::system_clock::now();
}

int64_t Clock::ElapsedMiliSeconds() {
    std::chrono::time_point<std::chrono::system_clock> CurrentTime;
    CurrentTime = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = CurrentTime - StartTime;

    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count();
}

int64_t Clock::ElapsedNanoSeconds() {
    std::chrono::time_point<std::chrono::system_clock> CurrentTime;
    CurrentTime = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = CurrentTime - StartTime;

    return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count();
}
