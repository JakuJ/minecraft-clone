#pragma once

#include <vector>
#include "buffers/buffers.hpp"
#include "world/chunk.hpp"

class World
{
    Chunk chunk;

public:
    World();
    void placeBlock(int, int, int, Cube::Type);
    void buffer(Buffers&);
};