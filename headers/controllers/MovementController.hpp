#pragma once

#include "controllers/InputController.hpp"

class MovementController : public InputController
{
public:
    MovementController(GLFWwindow *);

    void processKeyboard(int keyCode, float deltaTime) final;
    void processMouseMovement(float xoff, float yoff) final;
};