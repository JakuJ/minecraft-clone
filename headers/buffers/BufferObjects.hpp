#pragma once

#include <vector>
#include <iostream>
#include "glad/glad.h"

template <typename T>
struct BufferType
{
    static unsigned int const Type;
};

#pragma region BufferObject

template <typename T>
class BufferObject
{
protected:
    unsigned int id;
    size_t buffer_size;

    BufferObject() : buffer_size(0){};

    virtual size_t size() const = 0;
    void bufferVector(const std::vector<T> &, GLenum);
};

template <typename T>
inline void BufferObject<T>::bufferVector(const std::vector<T> &v, GLenum target)
{
    size_t currentSize = v.size() * sizeof(T);

    if (currentSize > buffer_size)
    {
        std::cout << "Reallocating a buffer!" << std::endl;
        glBufferData(target, currentSize, &v.front(), GL_DYNAMIC_DRAW);
        buffer_size = currentSize;
    }
    else
    {
        glBufferSubData(target, 0, currentSize, &v.front());
    }
}

#pragma endregion
#pragma region EBO

class EBO : BufferObject<unsigned int>
{
private:
    std::vector<unsigned int> indices;

public:
    EBO();

    size_t size() const override;

    void append(const std::vector<unsigned int> &vec);
    void clear();
    void bufferData();
};

#pragma endregion
#pragma region VBO

template <typename T, unsigned int N>
class VBO : BufferObject<T>
{
private:
    unsigned int location;
    std::vector<T> data;

public:
    VBO(unsigned int location) : location(location)
    {
        glGenBuffers(1, &(this->id));
        data = std::vector<T>();

        std::cout << "VBO created" << std::endl;
    };

    size_t size() const override
    {
        return data.size();
    };

    void append(const std::vector<T> &vec);
    void clear();
    void bufferData();
};

template <typename T, unsigned int N>
void VBO<T, N>::bufferData()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    this->bufferVector(data, GL_ARRAY_BUFFER);
    glVertexAttribPointer(location, N, BufferType<T>::Type, GL_FALSE, N * sizeof(T), (void *)0);
    glEnableVertexAttribArray(location);
}

template <typename T, unsigned int N>
void VBO<T, N>::append(const std::vector<T> &vec)
{
    data.insert(data.end(), vec.cbegin(), vec.cend());
}

template <typename T, unsigned int N>
void VBO<T, N>::clear()
{
    data.clear();
}

#pragma endregion