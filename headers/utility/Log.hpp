#pragma once

#include <iostream>

namespace Log {
    template<class... Args>
    void log(Args... args) {
        (std::cout << ... << args) << std::endl;
    }
}
