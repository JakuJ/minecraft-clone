#pragma once

#include "views/renderers/Renderer.hpp"
#include "buffers/VBO.hpp"

class SkyBoxRenderer : public Renderer {
    VBO<float, 3> vertices{4};

    void bufferData() final;

public:
    SkyBoxRenderer();

    void render() final;

    void fillBuffers() final;
};
