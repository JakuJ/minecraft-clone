# pragma once

#include "views/renderers/Renderer.hpp"
#include "buffers/VBO.hpp"

class SunRenderer : public Renderer {
    VBO<float, 3> vertices{5};

    void bufferData() final;

public:
    SunRenderer();

    void render() final;

    void fillBuffers() final;
};
