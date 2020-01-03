#include "buffers/EBO.hpp"
#include <iostream>

EBO::EBO()
{
    glGenBuffers(1, &id);
    indices = std::vector<unsigned int>();
    std::cout << "EBO created" << std::endl;
}

EBO::EBO(const std::vector<unsigned int> &indices) : EBO()
{
    append(indices);
}

void EBO::bufferData() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    bufferVector(GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW);
}

u_int EBO::size() const
{
    return indices.size();
}

void EBO::append(const std::vector<unsigned int> &vec)
{
    indices.insert(indices.end(), vec.cbegin(), vec.cend());
}

void EBO::clear()
{
    indices.clear();
}