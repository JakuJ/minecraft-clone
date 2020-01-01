#pragma once

#include "buffers/VBO.hpp"
#include "buffers/EBO.hpp"

struct Buffers
{
    VBO<float, 3> vertices;
    VBO<float, 3> texCoords;
    EBO indices;

public:
    size_t size;
    Buffers();
};