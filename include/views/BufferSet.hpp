#pragma once

#include <vector>
#include <memory>
#include "buffers/BufferObjects.hpp"

class BufferSet {
    unsigned int VAO{};

protected:
    std::vector<std::unique_ptr<VBOProxy>> vbos;

public:
    BufferSet();

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
