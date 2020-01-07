#pragma once

#include "rendering/program.hpp"
#include "views/BufferSet.hpp"
#include <memory>

class Renderer
{
protected:
    Program program;
    std::unique_ptr<BufferSet> buffers;

    size_t bufferedElements;

    Renderer(const std::string &, const std::string &);

    virtual void fillBuffers() = 0;
    void bufferData();

public:
    virtual ~Renderer() = default;
    virtual void render();
};



