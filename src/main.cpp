#include "window.hpp"
#include "world/world.hpp"
#include "player/player.hpp"
#include "utility/timing.hpp"
#include "rendering/renderer.hpp"

void fix_render_on_mac(GLFWwindow *window)
{
#ifdef __APPLE__
    static bool macMoved = false;
    if (!macMoved)
    {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        glfwSetWindowPos(window, ++x, y);
        macMoved = true;
    }
#endif
}

int main()
{
    const bool fullscreen = false;

    GLFWwindow *window = fullscreen ? setupWindow(2560, 1600, true) : setupWindow(800, 600);

    if (!window)
    {
        std::cout << "Aborting!" << std::endl;
        return -1;
    }

    World world;
    Player player(0, 80, 0);

    registerCamera(window, player.camera);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // For now, only the front-facing side of a transparent block is rendered
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW); // TODO: why is my winding order like this?

    glfwSwapInterval(1);

    unsigned int frames = 0;
    double lastSecond = glfwGetTime();
    double lastFrame = lastSecond;
    double currentTime = lastSecond;

    QuadRenderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        // pre-frame logic
        currentTime = glfwGetTime();

        // update player
        processInput(window, player.camera, currentTime - lastFrame);

        // render to screen
        glClearColor(0.6, 0.8, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.render(world, player);

        glfwSwapBuffers(window);

        // poll awaiting events
        glfwPollEvents();

        // print FPS to stdout
        if (currentTime - lastSecond >= 1.0)
        {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            lastSecond = currentTime;
        }

        lastFrame = currentTime;
        frames++;

        // fix rendering if on Mac OS
        fix_render_on_mac(window);
    }

    glfwTerminate();
    return 0;
}