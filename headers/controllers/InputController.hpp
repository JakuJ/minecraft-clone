#pragma once

#include "player/camera.hpp"
#include "window.hpp"

class Controller
{
    virtual void update() = 0;
};

class InputController : public Controller
{
    GLFWwindow* window;
    Camera camera;
    double timestamp;

public:
    InputController(GLFWwindow*);
    void update() final;
};
