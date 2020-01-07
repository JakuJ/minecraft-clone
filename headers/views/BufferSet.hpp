#pragma once

#include "buffers/BufferObjects.hpp"
#include <memory>
#include <vector>

class BufferSet
{
    unsigned int VAO;
    std::vector<std::unique_ptr<VBOProxy>> vbos;

public:
    BufferSet()
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        std::cout << "BufferSet created" << std::endl;
    };
    virtual ~BufferSet(){};
    BufferSet(const BufferSet &) = delete;
    BufferSet &operator=(const BufferSet &) = delete;

    virtual size_t elements() const;

    VBOProxy *operator[](unsigned int);

    void addVBO(VBOProxy *);

    virtual void clear();
    virtual void bufferData();
};

class IndexedBufferSet : public BufferSet
{
public:
    EBO ebo;

    size_t elements() const override;
    void clear() override;
    void bufferData() override;
};