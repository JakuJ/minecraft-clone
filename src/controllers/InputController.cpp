#include "controllers/InputController.hpp"
#include "models/Game.hpp"

InputController::InputController(GLFWwindow *window) : window(window), camera(0, 80, 0), timestamp(0)
{
    registerCamera(window, camera);
    Game::getInstance().player.camera = &camera;
}

void InputController::update()
{
    auto currentTime = glfwGetTime();
    processInput(window, camera, currentTime - timestamp);
    
    Game::getInstance().player.position = camera.position;
    
    timestamp = currentTime;
}