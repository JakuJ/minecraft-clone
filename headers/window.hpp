#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

GLFWwindow *setupWindow(int width, int height, bool fullScreen = false);
