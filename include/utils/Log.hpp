#pragma once

#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#define COLOR_SUPPORT 1
#define GREEN "\x1b[32m"
#define ORANGE "\x1b[38:2:255:165:0m"
#define RED "\x1b[31m"
#define RESET "\x1b[39;49m"
#else
#define COLOR_SUPPORT 0
#endif

#ifndef __unused
#define __unused __attribute__((unused))
#endif

#include <iostream>
#include <iomanip>
#include <string>

class Log {

public:
    enum Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

private:
    static Level loggingLevel;

    static auto getLevelMessage(Level level) {
        const char *messages[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
        return messages[level];
    }

    static void setColor(__unused Level level) {
#if COLOR_SUPPORT
        const char *colors[] = {"", GREEN, ORANGE, RED};
        std::cout << colors[level];
#endif
    }

    static void clearColor() {
#if COLOR_SUPPORT
        std::cout << RESET;
#endif
    }

    template<class... Args>
    static void logAt(Level level, Args... args) {
        if (level >= loggingLevel) {
            setColor(level);
            std::cout << std::setw(7) << getLevelMessage(level) << " -- ";
            clearColor();
            (std::cout << ... << args) << std::endl;
        }
    }

public:
    static void setLoggingLevel(Level level) {
        loggingLevel = level;
    }

    template<class... Args>
    static void debug(Args... args) {
        logAt(DEBUG, args...);
    }

    template<class... Args>
    static void info(Args... args) {
        logAt(INFO, args...);
    }

    template<class... Args>
    static void warn(Args... args) {
        logAt(WARNING, args...);
    }

    template<class... Args>
    static void error(Args... args) {
        logAt(ERROR, args...);
    }
};

