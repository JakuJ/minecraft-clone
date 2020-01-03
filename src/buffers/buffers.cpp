#include "buffers/buffers.hpp"
#include <iostream>

Buffers::Buffers()
{
    std::cout << "Buffers created" << std::endl;
}

u_int Buffers::size() const
{
    return indices.size();
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

void QuadBuffers::bufferData() const
{
    vertices.bufferData();
    indices.bufferData();
    texCoords.bufferData();
}