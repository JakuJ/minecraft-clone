#pragma once

#include "glad/glad.h"
#include <iostream>
#include <vector>

template<typename T>
struct BufferType {
    static unsigned int const Type;
};

template<typename T>
class BufferObject {
protected:
    unsigned int id{};
    size_t buffer_size;

    BufferObject() : buffer_size(0) {}

    [[nodiscard]] virtual size_t size() const = 0;

    void bufferVector(const std::vector<T> &, GLenum);
};

template<typename T>
inline void BufferObject<T>::bufferVector(const std::vector<T> &v, GLenum target) {
    size_t currentSize = v.size() * sizeof(T);

    if (currentSize > buffer_size) {
        std::cout << "Reallocating a buffer!" << std::endl;
        glBufferData(target, currentSize, &v.front(), GL_DYNAMIC_DRAW);
        buffer_size = currentSize;
    } else {
        glBufferSubData(target, 0, currentSize, &v.front());
    }
}

class EBO : BufferObject<unsigned int> {
private:
    std::vector<unsigned int> indices;

public:
    EBO();

    [[nodiscard]] size_t size() const override;

    void fill(const std::vector<unsigned int> &vec);

    void bufferData();
};

class VBOProxy {
public:
    virtual ~VBOProxy() = default;

    [[nodiscard]] virtual size_t size() const = 0;

    virtual void bufferData() = 0;
};

template<typename T, unsigned int N>
class VBO : public BufferObject<T>, public VBOProxy {
private:
    unsigned int location;
    std::vector<T> data;

public:
    static VBO<T, N> Create(unsigned int location) {
        return VBO<T, N>(location);
    }

    explicit VBO(unsigned int location) : location(location) {
        glGenBuffers(1, &(this->id));
        data = std::vector<T>();

        std::cout << "VBO created" << std::endl;
    }

    [[nodiscard]] size_t size() const override {
        return data.size() / N;
    }

    void fill(const std::vector<T> &vec);

    void bufferData() override;
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

#pragma endregion