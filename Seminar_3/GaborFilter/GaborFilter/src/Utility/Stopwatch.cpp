#include "Utility/Stopwatch.hpp"

Stopwatch::Stopwatch() noexcept {
    m_Running = false;
    m_StartTime = std::chrono::system_clock::now();
    m_EndTime = m_StartTime;
}

void Stopwatch::Start() noexcept {
    if (m_StartTime == m_EndTime) {
        Restart();
    } else {
        m_Running = true;
    }
}

void Stopwatch::Pause() noexcept {
    m_Running = false;
    m_EndTime = std::chrono::system_clock::now();
}

void Stopwatch::Reset() noexcept {
    m_Running = false;
    m_StartTime = std::chrono::system_clock::now();
    m_EndTime = m_StartTime;
}

void Stopwatch::Restart() noexcept {
    m_Running = true;
    m_StartTime = std::chrono::system_clock::now();
    m_EndTime = m_StartTime;
}

bool Stopwatch::IsRunning() const noexcept {
    return m_Running;
}

int64_t Stopwatch::ElapsedNanoseconds() const noexcept {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(Elapsed()).count();
}

int64_t Stopwatch::ElapsedMicroSeconds() const noexcept {
    return std::chrono::duration_cast<std::chrono::microseconds>(Elapsed()).count();
}

int64_t Stopwatch::ElapsedMiliseconds() const noexcept {
    return std::chrono::duration_cast<std::chrono::milliseconds>(Elapsed()).count();
}

int64_t Stopwatch::ElapsedSeconds() const noexcept {
    return std::chrono::duration_cast<std::chrono::seconds>(Elapsed()).count();
}

int64_t Stopwatch::ElapsedMinutes() const noexcept {
    return std::chrono::duration_cast<std::chrono::minutes>(Elapsed()).count();
}

int64_t Stopwatch::ElapsedHours() const noexcept {
    return std::chrono::duration_cast<std::chrono::hours>(Elapsed()).count();
}

std::chrono::duration<double> Stopwatch::Elapsed() const noexcept {
    if (IsRunning()) {
        const auto now = std::chrono::system_clock::now();
        return now - m_StartTime;
    }

    return m_EndTime - m_StartTime;
}
