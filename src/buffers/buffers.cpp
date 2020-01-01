#include "buffers/buffers.hpp"
#include <iostream>

Buffers::Buffers() : vertices(0), texCoords(1), size(0)
{
    std::cout << "Buffers created" << std::endl;
}