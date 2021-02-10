#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include "Controller.hpp"

/// An abstract class that can handle mouse and keyboard input.
class InputController : public Controller {
    void registerMouseHandler() const;

protected:
    GLFWwindow *window;

public:
    explicit InputController(GLFWwindow *);

    /// Process keyboard input that might've happened since the last update.
    void update() final;

    /// Keyboard input handler.
    virtual void processKeyboard(int keyCode, double deltaTime) = 0;

    /// Mouse movement handler.
    virtual void processMouseMovement(double xOff, double yOff) = 0;
};
