#include "buffers/buffers.hpp"
#include <iostream>

Buffers::Buffers()
{
    std::cout << "Buffers created" << std::endl;
}

QuadBuffers::QuadBuffers() : vertices(0), texCoords(1)
{
    std::cout << "CubeBuffers created" << std::endl;
}

void QuadBuffers::clear()
{
    vertices.clear();
    indices.clear();
    texCoords.clear();
}