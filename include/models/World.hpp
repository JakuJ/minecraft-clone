#pragma once

#include <vector>
#include "world/chunk.hpp"
#include "world/quadtree.hpp"

class World {
    static const unsigned int SIDE = 10;

public:
    QuadTree tree;

    World();

    void placeBlock(int, int, int, Block::Type);

    [[maybe_unused]] void removeBlock(int, int, int);
};
