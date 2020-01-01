#include "window.hpp"
#include "program.hpp"
#include "helpers.hpp"

void initBuffers()
{
    // Create a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create a Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send data to the buffer
    std::vector<float> vertices = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f   // top left
    };

    bufferVector(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

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

        program.setFloat("time", glfwGetTime());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        fix_render_on_mac(window);
    }

    glfwTerminate();
    return 0;
}