#pragma once

#include "views/renderers/AsyncRenderer.hpp"
#include "rendering/texture.hpp"

class QuadRenderer : public AsyncRenderer
{
    static const int RENDERING_DISTANCE = 12;

    IndexedBufferSet ibs;
    Texture2D texture;

public:
    QuadRenderer();

    void fillBuffersSync() final;
    void renderSync() final;
    void bufferData() override;
};
