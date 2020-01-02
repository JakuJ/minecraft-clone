#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "player/camera.hpp"

GLFWwindow *setupWindow(int width, int height);
void processInput(GLFWwindow *window, Camera &camera, float deltaTime);
void registerCamera(GLFWwindow *window, const Camera &camera);