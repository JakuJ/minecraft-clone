#pragma once

#include <vector>
#include <memory>
#include "buffers/BufferObjects.hpp"

class BufferSet {
    unsigned int VAO{};

protected:
    std::vector<std::unique_ptr<VBOProxy>> vbos;

public:
    BufferSet() {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        std::cout << "BufferSet created" << std::endl;
    }

    virtual ~BufferSet() = default;

    BufferSet(const BufferSet &) = delete;

    BufferSet &operator=(const BufferSet &) = delete;

    VBOProxy *operator[](unsigned int);

    void addVBO(VBOProxy *);

    virtual void bufferData();
};

class IndexedBufferSet : public BufferSet {
public:
    EBO ebo;

    void bufferData() override;
};
