#include <models/Game.hpp>
#include <glm/vec3.hpp>
#include "controllers/InputController.hpp"

InputController::InputController(GLFWwindow *window) : lastUpdate(0), window(window) {
    registerMouseHandler();
}

void InputController::update() {
    auto currentTime = glfwGetTime();

    const int keys[]{GLFW_KEY_ESCAPE,
                     GLFW_KEY_W,
                     GLFW_KEY_S,
                     GLFW_KEY_A,
                     GLFW_KEY_D,
                     GLFW_KEY_SPACE};

    double deltaTime = currentTime - lastUpdate;

    // PROCESS KEY PRESSES
    for (auto key : keys) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            processKeyboard(key, deltaTime);
        }
    }

    Game::getInstance().player.applyGravity(deltaTime);

    lastUpdate = currentTime;
}

void InputController::registerMouseHandler() const {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, const_cast<void *>(reinterpret_cast<void const *>(this)));
    glfwSetCursorPosCallback(window, [](GLFWwindow *w, double xPos, double yPos) {
        auto *self = static_cast<InputController *>(glfwGetWindowUserPointer(w));

        static double lastX = xPos;
        static double lastY = yPos;

        double xOffset = xPos - lastX;
        double yOffset = lastY - yPos;  // reversed since y-coordinates go from bottom to top

        lastX = xPos;
        lastY = yPos;

        self->processMouseMovement(xOffset, yOffset);
    });
}
