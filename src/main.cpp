#include "window.hpp"
#include "rendering/program.hpp"
#include "rendering/texture.hpp"
#include "buffers/buffers.hpp"
#include "world/world.hpp"
#include "player/player.hpp"
#include "player/camera.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

    // make an acacia tree
    const int tree_height = 5;
    for (int y = 0; y < tree_height; y++)
    {
        world.placeBlock(0, Chunk::SEA_LEVEL + 1 + y, 0, Block::ACACIA_LOG);
    }

    for (int x = 0; x < tree_height; x++)
    {
        for (int y = 0; y < tree_height; y++)
        {
            for (int z = 0; z < tree_height; z++)
            {
                world.placeBlock(x - tree_height / 2, Chunk::SEA_LEVEL + 1 + y + tree_height, z - tree_height / 2, Block::ACACIA_LEAVES);
            }
        }
    }

    Player player(0, Chunk::SEA_LEVEL + 2, 10);

    registerCamera(window, player.camera);

    glEnable(GL_DEPTH_TEST);

    // For now, only the front-facing side of a transparent block is rendered
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW); // TODO: why is my winding order like this?

    glfwSwapInterval(1);

    unsigned int frames = 0;
    double lastSecond = glfwGetTime();
    double lastFrame = lastSecond;
    double currentTime = lastSecond;

    while (!glfwWindowShouldClose(window))
    {
        // pre-frame logic
        currentTime = glfwGetTime();

        // update player
        processInput(window, player.camera, currentTime - lastFrame);

        // render to screen
        glClearColor(0.6, 0.8, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // update world
        world.update(player);

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