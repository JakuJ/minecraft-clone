#pragma once

#include "controllers/InputController.hpp"

class MovementController : public InputController {
public:
    explicit MovementController(GLFWwindow *);

    void processKeyboard(int keyCode, double deltaTime) final;

    void processMouseMovement(double xOff, double yOff) final;
};
