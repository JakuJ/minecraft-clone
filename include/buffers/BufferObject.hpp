#pragma once

#include <vector>
#include "glad/glad.h"
#include "utils/Log.hpp"

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
        Log::debug("Reallocating a buffer");
        glBufferData(target, currentSize, &v.front(), GL_DYNAMIC_DRAW);
        buffer_size = currentSize;
    } else {
        glBufferSubData(target, 0, currentSize, &v.front());
    }
}