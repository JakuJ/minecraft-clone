#pragma once

#include <vector>
#include "world/chunk.hpp"

class World
{
    static const unsigned int RENDER_DISTANCE = 1;
    Chunk chunks[World::RENDER_DISTANCE];

public:
    World();
    void placeBlock(int, int, int, Cube::Type);
};