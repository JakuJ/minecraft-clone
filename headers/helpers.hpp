#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>

template <typename T>
struct BufferType
{
    static unsigned int const type;
};

template <>
unsigned int const BufferType<float>::type = GL_FLOAT;

template <typename T>
inline void bufferVector(GLenum target, const std::vector<T> &v, GLenum usage)
{
    glBufferData(target, v.size() * sizeof(T), &v.front(), usage);
}

void fix_render_on_mac(GLFWwindow *window)
{
#ifdef __APPLE__
    static bool macMoved = false;
    if (!macMoved)
    {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        glfwSetWindowPos(window, ++x, y);
        macMoved = true;
    }
#endif
}