#pragma once

#include "window.hpp"

class Controller {
public:
    virtual void update() = 0;
};

class InputController : public Controller {
    double lastUpdate;

protected:
    GLFWwindow *window;

public:
    explicit InputController(GLFWwindow *);

    void registerMouseHandler() const;

    void update() final;

    virtual void processKeyboard(int keyCode, double deltaTime) = 0;

    virtual void processMouseMovement(double xOff, double yOff) = 0;
};
