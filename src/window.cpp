#include "window.hpp"
#include "utils/Log.hpp"

void framebuffer_size_callback(__unused GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *setupWindow(int width, int height, bool fullScreen) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(width, height, "Minecraft clone",
                                          fullScreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    if (!window) {
        Log::error("Failed to create GLFW window");
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        Log::error("Failed to initialize GLAD");
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, width, height);

    return window;
}
