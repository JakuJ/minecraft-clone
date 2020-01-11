#pragma once

#include "rendering/texture.hpp"
#include "views/renderers/AsyncRenderer.hpp"
#include "buffers/BufferObjects.hpp"


class InstancingRenderer : public AsyncRenderer {
    Texture2D texture;
    unsigned int bufferedInstances;

    VBO<float, 3> vertices{0};
    VBO<float, 2> texCoords{1};
    VBO<float, 3> offsets{2};
    VBO<float, 3> infos{3};

public:
    InstancingRenderer();

    void bufferData() override;

    void fillBuffersSync() final;

    void renderSync() final;
};
