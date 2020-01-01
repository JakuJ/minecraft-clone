#pragma once

#include "glad/glad.h"
#include <vector>
#include <iostream>

template <typename T>
struct BufferType
{
    static unsigned int const type;
};

template <typename T>
inline void bufferVector(GLenum target, const std::vector<T> &v, GLenum usage)
{
    glBufferData(target, v.size() * sizeof(T), &v.front(), usage);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
{
    for (T elem : v)
    {
        out << elem << " ";
    }
    return out;
}
