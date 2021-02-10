#include "buffers/EBO.hpp"

template<>
unsigned const BufferType<float>::Type = GL_FLOAT;

EBO::EBO() {
    glGenBuffers(1, &id);
}

void EBO::bufferData() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    bufferVector(data, GL_ELEMENT_ARRAY_BUFFER);
}

size_t EBO::size() const {
    return data.size();
}

