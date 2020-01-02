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
    QuadRenderer renderer;
    
    for (int x = -6; x <= 6; x++)
    {
        for (int z = -6; z <= 6; z++)
        {
            world.placeBlock(x, 0, z, Block::GRASS);
        }
    }

    world.placeBlock(-6, 2, -6, Block::DIRT);
    world.placeBlock(-6, 2, 6, Block::DIRT);
    world.placeBlock(6, 2, -6, Block::DIRT);
    world.placeBlock(6, 2, 6, Block::DIRT);

    world.placeBlock(0, 2, 0, Block::DIRT);

    // Render the world
    world.render(renderer);

    Player player(0, 2, 0);

    registerCamera(window, player.camera);

    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW); // why?

    glfwSwapInterval(1);

    unsigned int frames = 0;
    double lastSecond = glfwGetTime();
    double lastFrame = lastSecond;
    double currentTime = lastSecond;

    while (!glfwWindowShouldClose(window))
    {
        // pre-frame logic
        currentTime = glfwGetTime();
        processInput(window, player.camera, currentTime - lastFrame);

        glClearColor(0.6, 0.8, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 mvp = glm::mat4(1);
        mvp *= glm::perspective<float>(glm::radians(60.0), 800.0 / 600.0, 0.5, 2 * Chunk::SIDE);
        mvp *= player.camera.getViewMatrix();

        renderer.program.setUniform("mvp", mvp);

        renderer.render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (currentTime - lastSecond >= 1.0)
        {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            lastSecond = currentTime;
        }

        lastFrame = currentTime;
        frames++;

        fix_render_on_mac(window);
    }

    glfwTerminate();
    return 0;
}