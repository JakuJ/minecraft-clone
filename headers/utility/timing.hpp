#pragma once

#include <iostream>
#include <string>
#include <chrono>

class ScopeTimer
{
    std::chrono::high_resolution_clock::time_point start;
    std::string message;

public:
    ScopeTimer(const std::string &message) : message(message)
    {
        start = std::chrono::high_resolution_clock::now();
    };

    ~ScopeTimer()
    {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::cout << message << " [" << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns]" << std::endl;
    }
};