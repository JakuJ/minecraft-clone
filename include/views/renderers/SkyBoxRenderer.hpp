# pragma once

#include "views/renderers/Renderer.hpp"
#include "buffers/BufferObjects.hpp"

class SkyBoxRenderer : public Renderer {
    VBO<float, 3> vertices{4};

    void bufferData() override;

public:
    SkyBoxRenderer();

    void render() override;

    void fillBuffers() override;
};
