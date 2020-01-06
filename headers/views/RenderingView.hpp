#pragma once

#include "views/View.hpp"
#include "views/renderers/QuadRendererT.hpp"
#include "views/renderers/RendererT.hpp"
#include <memory>

class RenderingView : public View
{
protected:
    std::unique_ptr<RendererT> renderer;

public:
    void render() override
    {
        renderer->render();
    };
};

class QuadRenderingView : public RenderingView
{
public:
    QuadRenderingView()
    {
        renderer = std::make_unique<QuadRendererT>();
    }
};