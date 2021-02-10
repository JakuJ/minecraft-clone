#pragma once

#include <buffers/VBO.hpp>
#include <buffers/EBO.hpp>
#include "views/renderers/AsyncRenderer.hpp"
#include "rendering/Texture2D.hpp"

class QuadRenderer : public AsyncRenderer {
    Texture2D texture;

    VBO<float, 3> vertices{0};
    VBO<float, 3> normals{1};
    VBO<float, 2> texCoords{2};
    EBO indices;

public:
    QuadRenderer();

    void fillBuffersSync() final;

    void renderSync() final;

    void bufferData() override;
};
