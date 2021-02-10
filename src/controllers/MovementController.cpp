#include "controllers/MovementController.hpp"
#include "models/Game.hpp"

MovementController::MovementController(GLFWwindow *window) : InputController(window) {}

void MovementController::processKeyboard(int key, double deltaTime) {
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    auto vector = glm::vec3(deltaTime);

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
            Game::getInstance().player.jump();
            return;
        default:
            return;
    }

    // TODO: Remove God-class
    Game::getInstance().player.move(vector);
}

void MovementController::processMouseMovement(double xOff, double yOff) {
    static const double mouseSensitivity = 0.2;

    Player &player = Game::getInstance().player;

    player.headYaw += xOff * mouseSensitivity;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    player.headPitch = glm::clamp(player.headPitch + yOff * mouseSensitivity, -89.0, 89.0);
}
