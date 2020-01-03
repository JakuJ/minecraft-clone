#pragma once

#include "buffers/VBO.hpp"
#include "buffers/EBO.hpp"

struct Buffers
{
    EBO indices;

public:
    Buffers();
    virtual void clear() = 0;
};

struct QuadBuffers : public Buffers
{
    VBO<float, 3> vertices;
    VBO<float, 2> texCoords;

public:
    QuadBuffers();
    void clear() override;
};