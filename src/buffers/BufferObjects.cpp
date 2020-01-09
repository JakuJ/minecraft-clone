#include "buffers/BufferObjects.hpp"

template<>
unsigned int const BufferType<float>::Type = GL_FLOAT;

EBO::EBO() {
    glGenBuffers(1, &id);
    indices = std::vector<unsigned int>();
}

void EBO::bufferData() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    bufferVector(indices, GL_ELEMENT_ARRAY_BUFFER);
}

size_t EBO::size() const {
    return indices.size();
}

void EBO::fill(const std::vector<unsigned int> &vec) {
    indices.assign(vec.begin(), vec.end());
}
