#pragma once

#include "window.hpp"

class Controller
{
public:
    virtual void update() = 0;
};

class InputController : public Controller
{
    double lastUpdate;

protected:
    GLFWwindow *window;

public:
    InputController(GLFWwindow *);

    void registerMouseHandler() const;

    void update() final;

    virtual void processKeyboard(int keyCode, float deltaTime) = 0;
    virtual void processMouseMovement(float xoff, float yoff) = 0;
};
