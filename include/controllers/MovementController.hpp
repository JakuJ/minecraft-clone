#pragma once

#include <models/Player.hpp>
#include "controllers/InputController.hpp"

/// Input controller responsible for player movement.
class MovementController final : public InputController {
    Player& player;

public:
    MovementController(Player& player, GLFWwindow *);

    void processKeyboard(int keyCode, double deltaTime) final;

    void processMouseMovement(double xOff, double yOff) final;
};
