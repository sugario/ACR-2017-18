#ifndef UTILITY_CLOCK_HPP
#define UTILITY_CLOCK_HPP

#include <chrono>

class Clock {
 public:
    Clock() noexcept;

    void Start() noexcept;
    int64_t ElapsedMiliSeconds() const noexcept;
    int64_t ElapsedNanoSeconds() const noexcept;

 private:
    std::chrono::time_point<std::chrono::system_clock> StartTime;
};

#endif  // !UTILITY_CLOCK_HPP
