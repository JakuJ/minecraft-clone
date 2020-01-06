#pragma once

#include "rendering/program.hpp"
#include "views/BufferSet.hpp"
#include <memory>

class RendererT
{
protected:
    Program program;
    std::unique_ptr<BufferSet> buffers;

    size_t bufferedElements;

    RendererT(const std::string &, const std::string &);

    virtual void fillBuffers() = 0;
    void bufferData();

public:
    virtual ~RendererT(){};
    virtual void render() = 0;
};



