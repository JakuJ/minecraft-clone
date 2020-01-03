#pragma once

#include <vector>
#include "buffers/buffers.hpp"
#include "world/chunk.hpp"
#include "quadtree.hpp"
#include "rendering/renderer.hpp"
#include "player/player.hpp"

class World
{
    static const unsigned int SIDE = 10;
    QuadTree tree;
    QuadRenderer renderer;

    void sendData(float x, float z);

public:
    World();
    void placeBlock(int, int, int, Block::Type);
    void removeBlock(int, int, int);
    
    // rendering
    void update(Player &);
};