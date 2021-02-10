#pragma once

#include <vector>
#include "buffers/BufferObject.hpp"

template<typename T, unsigned int N>
class VBO : public BufferObject<T> {
    unsigned int location;

public:
    explicit VBO(unsigned int location) : location(location) {
        glGenBuffers(1, &(this->id));
    }

    /// Gets the number of vertices in the internal vector (its size / vertex dimensions)
    [[nodiscard]] size_t size() const override {
        return this->data.size() / N;
    }

    void bufferData() override;
};

template<typename T, unsigned int N>
void VBO<T, N>::bufferData() {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    this->bufferVector(this->data, GL_ARRAY_BUFFER);
    glVertexAttribPointer(location, N, BufferType<T>::Type, GL_FALSE, N * sizeof(T), reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(location);
}
