#pragma once

#include <memory>
#include "views/View.hpp"
#include "views/renderers/QuadRenderer.hpp"
#include "views/renderers/Renderer.hpp"

class RenderingView : public View {
protected:
    std::unique_ptr<Renderer> renderer;

public:
    explicit RenderingView(Renderer *renderer);

    void refresh() override;
};

