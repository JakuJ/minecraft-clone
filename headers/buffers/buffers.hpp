#pragma once

#include "buffers/VBO.hpp"
#include "buffers/EBO.hpp"

struct Buffers
{
    EBO indices;

public:
    Buffers();
};

struct QuadBuffers : public Buffers
{
    VBO<float, 3> vertices;
    VBO<float, 2> texCoords;

public:
    QuadBuffers();
};