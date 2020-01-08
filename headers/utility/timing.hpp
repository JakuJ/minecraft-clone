#pragma once

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <chrono>

typedef std::milli unit;

class Timer {
protected:
    std::chrono::steady_clock::time_point start;
    std::string message;

public:
    explicit Timer(std::string message);
};

class ScopedTimer : Timer {
public:
    explicit ScopedTimer(const std::string &message);

    ~ScopedTimer();
};

class MeanScopedTimer : Timer {
    static std::map<std::string, std::pair<double, double>> times;

public:
    explicit MeanScopedTimer(const std::string &message);

    ~MeanScopedTimer();
};
