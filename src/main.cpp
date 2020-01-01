#include "window.hpp"
#include "program.hpp"
#include "buffer.hpp"
#include "helpers.hpp"

void initBuffers()
{
    // Create a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create a Vertex Buffer Objects

    std::vector<float> vertices = {
        0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0,
        -0.5, 0.5, 0.0};

    VertexBuffer<float, 3> vbo1(0);
    vbo1.bufferData(vertices);

    std::vector<float> colors = {
        1, 1, 1,
        0, 0, 0,
        1, 0, 1,
        0, 1, 0};

    VertexBuffer<float, 3> vbo2(1);
    vbo2.bufferData(colors);

    // Create an Element Buffer Object
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Send data to the buffer
    std::vector<unsigned int> indices = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    bufferVector(GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW);
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

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.setUniform("time", (float)glfwGetTime());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        fix_render_on_mac(window);
    }

    glfwTerminate();
    return 0;
}