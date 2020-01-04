#include "buffers/BufferObjects.hpp"

template <>
unsigned int const BufferType<float>::Type = GL_FLOAT;

EBO::EBO()
{
    glGenBuffers(1, &id);
    indices = std::vector<unsigned int>();
    std::cout << "EBO created" << std::endl;
}

void EBO::bufferData()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    bufferVector(indices, GL_ELEMENT_ARRAY_BUFFER);
}

size_t EBO::size() const
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