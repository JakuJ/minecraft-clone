#pragma once

#include <vector>
#include <iostream>
#include "buffers/helpers.hpp"

template <typename T, unsigned int N>
class VBO
{
private:
    unsigned int id;
    unsigned int location;
    std::vector<T> data;

    void bufferData() const;

public:
    VBO(unsigned int location) : location(location)
    {
        glGenBuffers(1, &id);
        data = std::vector<float>();
        std::cout << "VBO created" << std::endl;
    };
    VBO(unsigned int location, const std::vector<T> &data) : VBO(location)
    {
        append(data);
    };

    void append(const std::vector<T> &vec);
    void clear();
};

template <typename T, unsigned int N>
void VBO<T, N>::bufferData() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    bufferVector(GL_ARRAY_BUFFER, data, GL_STATIC_DRAW);
    glVertexAttribPointer(location, N, BufferType<T>::type, GL_FALSE, N * sizeof(T), (void *)0);
    glEnableVertexAttribArray(location);
}

template <typename T, unsigned int N>
void VBO<T, N>::append(const std::vector<T> &vec)
{
    data.insert(data.end(), vec.cbegin(), vec.cend());
    bufferData();
}

template <typename T, unsigned int N>
void VBO<T, N>::clear()
{
    data.clear();
    bufferData();
}