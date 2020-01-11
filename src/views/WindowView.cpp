#include <glad/glad.h>
#include <utils/Log.hpp>
#include <views/WindowView.hpp>

#ifndef __unused
#define __unused __attribute__((unused))
#endif

WindowView::WindowView(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, "I can't believe it's not Minecraft!", nullptr, nullptr);

    if (!window) {
        auto message = "Failed to create GLFW window";
        Log::error(message);
        glfwTerminate();
        throw std::runtime_error(message);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        auto message = "Failed to initialize GLAD";
        Log::error(message);
        throw std::runtime_error(message);
    }

    // Set initial viewport and resize with the window
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, [](__unused GLFWwindow *win, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // For now, only the front-facing side of a transparent block is rendered
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);  // TODO: why is my winding order like this?

    // VSYNC
    glfwSwapInterval(1);

    // Global vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

WindowView::~WindowView() {
    glfwTerminate();
}

void WindowView::mainLoop(Controller *controller) {
    while (!glfwWindowShouldClose(window)) {
        // update player
        controller->update();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // NOLINT
        refresh();

        glfwSwapBuffers(window);
        glfwPollEvents();

        // fix rendering if on Mac OS
#ifdef __APPLE__
        static bool macMoved = false;
        if (!macMoved) {
            int x, y;
            glfwGetWindowPos(window, &x, &y);
            glfwSetWindowPos(window, ++x, y);
            macMoved = true;
            Log::info("On macOS, fixed rendering");
        }
#endif
    }
}

GLFWwindow *WindowView::getWindow() const {
    return window;
}
