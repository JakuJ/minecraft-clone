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
    Texture texture1("textures/dirt/side.jpg", GL_TEXTURE0, true);
    program.setUniform("dirt", 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

    world.placeBlock(0, 0, 0, Cube::DIRT);
    world.placeBlock(0, 0, 1, Cube::DIRT);
    world.placeBlock(1, 0, 1, Cube::DIRT);
    world.placeBlock(1, 0, 0, Cube::AIR);

    // Render the world
    world.buffer(buffers);
    initTextures(program);

    Player player;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW); // why?

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 mvp = glm::mat4(1);
        mvp = glm::rotate(mvp, (float)glfwGetTime(), glm::vec3(0, 1, 0));
        mvp = glm::lookAt(glm::vec3(0, 4, 4), glm::vec3(0), glm::vec3(0, 1, 0)) * mvp;
        mvp = glm::perspective<float>(glm::radians(60.0), 800.0 / 600.0, 1, 20) * mvp;
        
        program.setUniform("mvp", mvp);

        glDrawElements(GL_TRIANGLES, buffers.size, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        fix_render_on_mac(window);
    }

    glfwTerminate();
    return 0;
}