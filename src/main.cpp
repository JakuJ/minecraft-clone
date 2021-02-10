#include <views/WindowView.hpp>
#include <views/renderers/SkyBoxRenderer.hpp>
#include <views/renderers/InstancingRenderer.hpp>
#include <models/Game.hpp>
#include "controllers/MovementController.hpp"
#include "views/RenderingView.hpp"

int main() {
    Log::setLoggingLevel(Log::Level::DEBUG);

    std::unique_ptr<WindowView> windowView;
    try {
        windowView = std::make_unique<WindowView>(800, 600);
    } catch (std::exception &e) {
        exit(EXIT_FAILURE);
    }

    auto renderer = new QuadRenderer();
    renderer->fillBuffers();

    windowView->addView(new RenderingView(new SkyBoxRenderer()));
    windowView->addView(new RenderingView(renderer));

    MovementController controller(Game::getInstance().player, windowView->getWindow());

    windowView->mainLoop(&controller);

    Log::info("Program exited successfully");
    return 0;
}
