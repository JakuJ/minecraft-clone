#include "window.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "buffers/VBO.hpp"
#include "buffers/EBO.hpp"
#include "shape.hpp"

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

void initBuffers()
{
    // Create a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create buffers
    VBO<float, 3> vertices(0);
    VBO<float, 2> texCoords(1);
    EBO indices;

    // Define geometry
    Shape box = Shape::Box(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0.5, 0.5, 0.5));
    box.buffer(vertices, indices, texCoords);
}

void initTextures(const Program &program)
{
    Texture texture1("textures/container.jpg", GL_TEXTURE0);
    program.setUniform("box", 0);

    Texture texture2("textures/awesomeface.png", GL_TEXTURE1, true);
    program.setUniform("face", 1);

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

    initBuffers();
    initTextures(program);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 mvp = glm::mat4(1);
        mvp = glm::rotate(mvp, (float)glfwGetTime(), glm::vec3(0.5, 1, 0));
        program.setUniform("mvp", mvp);

        glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        fix_render_on_mac(window);
    }

    glfwTerminate();
    return 0;
}