#include "controllers/MovementController.hpp"
#include "models/Game.hpp"

MovementController::MovementController(Player &player, GLFWwindow *window)
        : InputController(window), player(player) {}

void MovementController::processKeyboard(int key, double deltaTime) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    auto vector = glm::vec3(deltaTime);

    // Hold left shift to run
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        vector *= 2;
    }

    switch (key) {
        case GLFW_KEY_W:
            vector *= glm::vec3(0, 0, -1);
            break;
        case GLFW_KEY_S:
            vector *= glm::vec3(0, 0, 1);
            break;
        case GLFW_KEY_A:
            vector *= glm::vec3(-1, 0, 0);
            break;
        case GLFW_KEY_D:
            vector *= glm::vec3(1, 0, 0);
            break;
        case GLFW_KEY_SPACE:
            player.jump();
            return;
        default:
            return;
    }

    player.move(vector);
}

void MovementController::processMouseMovement(double xOff, double yOff) {
    static const double mouseSensitivity = 0.2;

    player.headYaw += xOff * mouseSensitivity;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    player.headPitch = glm::clamp(player.headPitch + yOff * mouseSensitivity, -89.0, 89.0);
}
