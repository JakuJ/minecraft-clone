#pragma once

#include "rendering/texture.hpp"
#include "views/renderers/AsyncRenderer.hpp"

class InstancingRenderer : public AsyncRenderer {
    static const int RENDERING_DISTANCE = 8;

    Texture2D texture;
    unsigned int bufferedInstances;

public:
    InstancingRenderer();

    void bufferData() override;

    void fillBuffersSync() final;

    void renderSync() final;
};
