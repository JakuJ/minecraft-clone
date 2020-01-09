#include "utils/Log.hpp"
#include "controllers/MovementController.hpp"
#include "views/RenderingView.hpp"
#include "views/renderers/InstancingRenderer.hpp"

void fix_render_on_mac(GLFWwindow *window) {
#ifdef __APPLE__
    static bool macMoved = false;
    if (!macMoved) {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        glfwSetWindowPos(window, ++x, y);
        macMoved = true;
    }
#endif
}

int main() {
    GLFWwindow *window = setupWindow(800, 600);

    if (!window) {
        Log::error("Couldn't create a window!");
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // For now, only the front-facing side of a transparent block is rendered
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);  // TODO: why is my winding order like this?

    glfwSwapInterval(1);

    unsigned int frames = 0;
    double currentTime, lastSecond = glfwGetTime();

    MovementController controller(window);

    CompositeView view;
    view.add(new RenderingView(new QuadRenderer()));

    while (!glfwWindowShouldClose(window)) {
        // pre-frame logic
        currentTime = glfwGetTime();

        // update player
        controller.update();

        // render to screen
        glClearColor(0.6, 0.8, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT

        view.refresh();

        glfwSwapBuffers(window);

        // poll awaiting events
        glfwPollEvents();

        // print FPS to stdout
        if (currentTime - lastSecond >= 1.0) {
            Log::info("FPS: ", frames);
            frames = 0;
            lastSecond = currentTime;
        }

        frames++;

        // fix rendering if on Mac OS
        fix_render_on_mac(window);
    }

    glfwTerminate();
    return 0;
}
