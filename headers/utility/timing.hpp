#pragma once

#include <iostream>
#include <string>
#include <chrono>

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
    static const size_t TIMERS = 8;

    static long long times[TIMERS];
    static int samples[TIMERS];

    u_int index;

public:
    MeanScopedTimer(const std::string &message, u_int index);
    ~MeanScopedTimer();
};