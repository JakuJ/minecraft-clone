#pragma once

#include <string>
#include <memory>
#include "rendering/program.hpp"

class Renderer {
protected:
    Program program;

    size_t bufferedElements;

    Renderer(const std::string &, const std::string &);

    virtual void bufferData() = 0;

public:
    virtual ~Renderer() = default;

    virtual void render();

    virtual void fillBuffers() = 0;
};
