#pragma once

#include <vector>
#include "world/chunk.hpp"
#include "quadtree.hpp"

class World {
    static const unsigned int SIDE = 10;

public:
    QuadTree tree;

    World();

    void placeBlock(int, int, int, Block::Type);

    void removeBlock(int, int, int);
};