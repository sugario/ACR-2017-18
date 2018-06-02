#ifndef UTILITY_STOPWATCH_HPP
#define UTILITY_STOPWATCH_HPP

#include <cstdint>
#include <chrono>

struct Stopwatch {
    Stopwatch() noexcept;

    void Start() noexcept;
    void Pause() noexcept;
    void Reset() noexcept;
    void Restart() noexcept;

    bool IsRunning() const noexcept;

    int64_t ElapsedNanoseconds() const noexcept;
    int64_t ElapsedMicroSeconds() const noexcept;
    int64_t ElapsedMiliseconds() const noexcept;
    int64_t ElapsedSeconds() const noexcept;
    int64_t ElapsedMinutes() const noexcept;
    int64_t ElapsedHours() const noexcept;

private:
    std::chrono::duration<double> Elapsed() const noexcept;

    bool m_Running;
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
};

#endif  // !UTILITY_STOPWATCH_HPP
