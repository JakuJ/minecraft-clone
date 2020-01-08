#include "views/RenderingView.hpp"

void RenderingView::refresh() {
    renderer->render();
}

RenderingView::RenderingView(Renderer *renderer) {
    this->renderer = std::unique_ptr<Renderer>(renderer);
}
