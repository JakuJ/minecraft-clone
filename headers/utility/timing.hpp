#pragma once

#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <utility>

typedef std::milli unit;

class Timer
{
protected:
    std::chrono::steady_clock::time_point start;
    std::string message;

public:
    Timer(const std::string &message);
};

class ScopedTimer : Timer
{
public:
    ScopedTimer(const std::string &message);
    ~ScopedTimer();
};

class MeanScopedTimer : Timer
{
    static std::map<std::string, std::pair<double, double>> times;

public:
    MeanScopedTimer(const std::string &message);
    ~MeanScopedTimer();
};
