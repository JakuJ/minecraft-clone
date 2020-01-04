#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <utility>

typedef std::chrono::nanoseconds unit;

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
    static std::map<std::string, std::pair<long long, long long>> times;

public:
    MeanScopedTimer(const std::string &message);
    ~MeanScopedTimer();
};