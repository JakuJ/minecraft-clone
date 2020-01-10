#pragma once

#include <buffers/BufferObjects.hpp>
#include "views/renderers/AsyncRenderer.hpp"
#include "rendering/texture.hpp"

class QuadRenderer : public AsyncRenderer {
    static const int RENDERING_DISTANCE = 12;

    Texture2D texture;

    VBO<float, 3> vertices{0};
    VBO<float, 2> texCoords{1};
    EBO indices;

public:
    QuadRenderer();

    void fillBuffersSync() final;

    void renderSync() final;

    void bufferData() override;
};
