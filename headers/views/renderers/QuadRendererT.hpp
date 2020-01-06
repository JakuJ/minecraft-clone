#pragma once

#include "views/renderers/AsyncRenderer.hpp"
#include "rendering/texture.hpp"

class QuadRendererT : public AsyncRenderer
{
    static const int RENDERING_DISTANCE = 12;

    IndexedBufferSet ibs;
    Texture2D texture;

public:
    QuadRendererT();

    void fillBuffersSync() final;
    void renderSync() final;
};
