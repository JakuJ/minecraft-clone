#include "utility/timing.hpp"

#include <utility>

Timer::Timer(std::string message) : message(std::move(message)) {
    start = std::chrono::steady_clock::now();
}

ScopedTimer::ScopedTimer(const std::string &message) : Timer(message) {}

ScopedTimer::~ScopedTimer() {
    auto end = std::chrono::steady_clock::now();
    std::cout << message << "\t[" << std::chrono::duration<double, unit>(end - start).count() << " ms]" << std::endl;
}

std::map<std::string, std::pair<double, double>> MeanScopedTimer::times;

MeanScopedTimer::MeanScopedTimer(const std::string &message) : Timer(message) {
    times.try_emplace(message, std::make_pair(0, 0));
}

MeanScopedTimer::~MeanScopedTimer() {
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration<double, unit>(end - start).count();

    times[message].first += elapsed;
    times[message].second++;

    auto mean = times[message].first / times[message].second;

    std::cout << message << "\t[" << elapsed << " ms]\tMean: [" << mean << " ms]" << std::endl;
}
