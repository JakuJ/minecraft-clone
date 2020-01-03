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
    GLFWwindow *window = setupWindow(800, 600);

    if (!window)
    {
        std::cout << "Aborting!" << std::endl;
        return -1;
    }

    World world;

    const int side = 2;

    for (int x = -side; x <= side; x++)
    {
        for (int z = -side; z <= side; z++)
        {
            world.placeBlock(x, 142, z, Block::ACACIA_LEAVES);
            world.placeBlock(x, 140, z, Block::ACACIA_LOG);
            world.placeBlock(x, 138, z, Block::COBBLESTONE);
            world.placeBlock(x, 136, z, Block::GRASS);
            world.placeBlock(x, 134, z, Block::DIRT);
            world.placeBlock(x, 132, z, Block::STONE);
            world.placeBlock(x, 130, z, Block::ACACIA_LEAVES);
        }
    }

    Player player(2, 130, 15);

    registerCamera(window, player.camera);

    glEnable(GL_DEPTH_TEST);

    // TODO: Find a way not to cull transparent blocks
    // For now, face culling is disabled
    // glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CW); // TODO: why is my winding order wrong?

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