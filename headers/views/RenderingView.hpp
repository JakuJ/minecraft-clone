#pragma once

#include "views/View.hpp"
#include "views/renderers/QuadRenderer.hpp"
#include "views/renderers/Renderer.hpp"
#include <memory>

class RenderingView : public View
{
protected:
    std::unique_ptr<Renderer> renderer;

public:
    void refresh() override
    {
        renderer->render();
    };
};

class QuadRenderingView : public RenderingView
{
public:
    QuadRenderingView()
    {
        renderer = std::make_unique<QuadRenderer>();
    }
};