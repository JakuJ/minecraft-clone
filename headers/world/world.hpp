#pragma once

#include <vector>
#include "buffers/buffers.hpp"
#include "world/chunk.hpp"
#include "quadtree.hpp"
#include "rendering/renderer.hpp"

class World
{
    static const unsigned int SIDE = 1;
    QuadTree tree;

public:
    World();
    void placeBlock(int, int, int, Block::Type);
    void removeBlock(int, int, int);
    void render(QuadRenderer &) const;
};