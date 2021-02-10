#pragma once

#include <vector>
#include "glad/glad.h"
#include "utils/Log.hpp"

/// Used for compile-time mapping from C++ to OpenGL types
template<typename T>
struct BufferType {
    static const unsigned Type;
};

/// An abstraction over OpenGL buffers that holds data
/// in a vector before writing it to the actual buffer.
template<typename T>
class BufferObject {
    size_t buffer_size{};

protected:
    /// Buffer ID
    unsigned int id;

    /// A vector for storing data before writing it to the actual buffer
    std::vector<T> data{};

    /// Write data to the buffer, reallocating if necessary
    void bufferVector(const std::vector<T> &, GLenum);

    /// Gets the size of the internal vector
    [[nodiscard]] virtual size_t size() const = 0;

public:
    /// Set data to be written to the buffer
    void fill(const std::vector<T> &vec);

    /// Write data to the buffer
    virtual void bufferData() = 0;
};

template<typename T>
inline void BufferObject<T>::fill(const std::vector<T> &v) {
    data.assign(v.cbegin(), v.cend());
}

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