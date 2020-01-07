#include "controllers/MovementController.hpp"
#include "models/Game.hpp"

MovementController::MovementController(GLFWwindow *window) : InputController(window) {}

void MovementController::processKeyboard(int key, float deltaTime)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    glm::vec3 vector = glm::vec3(deltaTime);

    switch (key)
    {
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
    case GLFW_KEY_LEFT_SHIFT:
        vector *= glm::vec3(0, 1, 0);
        break;
    case GLFW_KEY_Z:
        vector *= glm::vec3(0, -1, 0);
        break;
    default:
        return;
    }

    Game::getInstance().player.move(vector);
}

void MovementController::processMouseMovement(float xoff, float yoff)
{
    static const float mouseSensitivity = 0.2;

    Player &player = Game::getInstance().player;

    player.headYaw += xoff * mouseSensitivity;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    player.headPitch = glm::clamp(player.headPitch + yoff * mouseSensitivity, -89.0f, 89.0f);
}