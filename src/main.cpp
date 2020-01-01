#include "window.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "buffers/buffers.hpp"
#include "shape.hpp"
#include "world/world.hpp"
#include "world/player.hpp"

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

void initTextures(const Program &program)
{
    CubeTexture dirtTexture("textures/dirt", GL_TEXTURE0, false);
    program.setUniform("dirt", 0);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

int main()
{
    GLFWwindow *window = setupWindow(800, 600);

    if (!window)
    {
        std::cout << "Aborting!" << std::endl;
        return -1;
    }

    Program program;
    program.use();

    // Create a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create buffers
    Buffers buffers;

    // Create a world
    World world;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            world.placeBlock(i, 0, j, Cube::DIRT);
        }
    }

    // Render the world
    world.buffer(buffers);
    initTextures(program);

    Player player;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW); // why?

    glfwSwapInterval(1);

    unsigned int frames = 0;
    double lastTime = glfwGetTime();
    double currentTime;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 mvp = glm::mat4(1);
        mvp *= glm::perspective<float>(glm::radians(60.0), 800.0 / 600.0, 1, 50);
        mvp *= glm::lookAt(glm::vec3(0, 4, 5), glm::vec3(0), glm::vec3(0, 1, 0));
        mvp = glm::rotate(mvp, (float)glfwGetTime(), glm::vec3(0, 1, 0));
        mvp = glm::translate(mvp, glm::vec3(-5, 0, -5));

        program.setUniform("mvp", mvp);

        glDrawElements(GL_TRIANGLES, buffers.size, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        currentTime = glfwGetTime();
        if (currentTime - lastTime >= 1.0)
        {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            lastTime = currentTime;
        }
        frames++;

        fix_render_on_mac(window);
    }

    glfwTerminate();
    return 0;
}