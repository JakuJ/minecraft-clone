#pragma once

#include <vector>
#include "helpers.hpp"

template <typename T, unsigned int N>
class VertexBuffer
{
private:
    unsigned int id;
    unsigned int location;

public:
    void bufferData(const std::vector<T> &data) const;
    VertexBuffer(unsigned int location);
};

template <typename T, unsigned int N>
VertexBuffer<T, N>::VertexBuffer(unsigned int location)
{
    glGenBuffers(1, &id);
    this->location = location;
}

template <typename T, unsigned int N>
void VertexBuffer<T, N>::bufferData(const std::vector<T> &data) const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    bufferVector(GL_ARRAY_BUFFER, data, GL_STATIC_DRAW);
    glVertexAttribPointer(location, N, BufferType<T>::type, GL_FALSE, N * sizeof(T), (void *)0);
    glEnableVertexAttribArray(location);
}