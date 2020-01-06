#include "controllers/InputController.hpp"
#include "models/Game.hpp"

InputController::InputController(GLFWwindow *window) : lastUpdate(0), window(window)
{
    registerMouseHandler();
}

void InputController::update()
{
    auto currentTime = glfwGetTime();

    const int keys[]{GLFW_KEY_ESCAPE,
                     GLFW_KEY_W,
                     GLFW_KEY_S,
                     GLFW_KEY_A,
                     GLFW_KEY_D,
                     GLFW_KEY_LEFT_SHIFT,
                     GLFW_KEY_Z};

    // PROCESS KEYPRESSES
    for (auto key : keys)
    {
        if (glfwGetKey(window, key) == GLFW_PRESS)
        {
            processKeyboard(key, currentTime - lastUpdate);
        }
    }

    lastUpdate = currentTime;
}

void InputController::registerMouseHandler() const
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, (void *)this);
    glfwSetCursorPosCallback(window, [](GLFWwindow *w, double xpos, double ypos) {
        InputController *self = static_cast<InputController *>(glfwGetWindowUserPointer(w));

        static float lastX = xpos;
        static float lastY = ypos;

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        self->processMouseMovement(xoffset, yoffset);
    });
}