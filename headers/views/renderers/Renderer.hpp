#pragma once

#include <string>
#include <memory>
#include "views/BufferSet.hpp"
#include "rendering/program.hpp"

class Renderer {
protected:
    Program program;
    std::unique_ptr<BufferSet> buffers;

    size_t bufferedElements;

    Renderer(const std::string &, const std::string &);

    virtual void fillBuffers() = 0;

    virtual void bufferData();

public:
    virtual ~Renderer() = default;

    virtual void render();
};



