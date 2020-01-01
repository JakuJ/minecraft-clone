#pragma once

#include <vector>
#include "buffers/buffers.hpp"
#include "world/chunk.hpp"
#include "quadtree.hpp"

class World
{
    static const unsigned int SIDE = 1;
    QuadTree tree;

public:
    World();
    void placeBlock(int, int, int, Cube::Type);
    void buffer(Buffers&);
};