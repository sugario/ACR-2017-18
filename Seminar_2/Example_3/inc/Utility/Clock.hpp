#ifndef UTILITY_CLOCK_HPP
#define UTILITY_CLOCK_HPP

#include <chrono>

class Clock {
 public:
    Clock();

    void Start();
    int64_t ElapsedMiliSeconds();
    int64_t ElapsedNanoSeconds();

 private:
    std::chrono::time_point<std::chrono::system_clock> StartTime;
};

#endif  // !UTILITY_CLOCK_HPP