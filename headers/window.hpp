#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

GLFWwindow *setupWindow(int width, int height);
void processInput(GLFWwindow *window);