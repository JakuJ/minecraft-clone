#include "utility/timing.hpp"

Timer::Timer(const std::string &message) : message(message)
{
    start = std::chrono::steady_clock::now();
}

ScopedTimer::ScopedTimer(const std::string &message) : Timer(message) {}

ScopedTimer::~ScopedTimer()
{
    auto end = std::chrono::steady_clock::now();
    std::cout << message << " [" << std::chrono::duration_cast<unit>(end - start).count() << " ns]" << std::endl;
}

long long MeanScopedTimer::times[] = {0};
int MeanScopedTimer::samples[] = {0};

MeanScopedTimer::MeanScopedTimer(const std::string &message, u_int index) : Timer(message), index(index) {}

MeanScopedTimer::~MeanScopedTimer()
{
    auto end = std::chrono::steady_clock::now();
    long long elapsed = std::chrono::duration_cast<unit>(end - start).count();

    times[index] += elapsed;
    samples[index]++;

    auto mean = times[index] / samples[index];

    std::cout << message << " [" << elapsed << " ns]" << std::endl;
    std::cout << "Mean: [" << mean << " ns]" << std::endl;
}
