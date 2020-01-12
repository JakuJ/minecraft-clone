#pragma once

#include <vector>
#include "buffers/BufferObject.hpp"
#include "glad/glad.h"

template<typename T, unsigned int N>
class VBO : public BufferObject<T> {
private:
    unsigned int location;
    std::vector<T> data;

public:
    explicit VBO(unsigned int location) : location(location) {
        glGenBuffers(1, &(this->id));
        data = std::vector<T>();
    }

    [[nodiscard]] size_t size() const override {
        return data.size() / N;
    }

    void fill(const std::vector<T> &vec);

    void bufferData();
};

template<typename T, unsigned int N>
void VBO<T, N>::bufferData() {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    this->bufferVector(data, GL_ARRAY_BUFFER);
    glVertexAttribPointer(location, N, BufferType<T>::Type, GL_FALSE, N * sizeof(T), reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(location);
}

template<typename T, unsigned int N>
void VBO<T, N>::fill(const std::vector<T> &vec) {
    data.assign(vec.begin(), vec.end());
}
