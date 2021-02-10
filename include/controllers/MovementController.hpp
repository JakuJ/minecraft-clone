#pragma once

#include "controllers/InputController.hpp"

/// Input controller responsible for player movement
class MovementController final : public InputController {
public:
    explicit MovementController(GLFWwindow *);

    void processKeyboard(int keyCode, double deltaTime) final;

    void processMouseMovement(double xOff, double yOff) final;
};
