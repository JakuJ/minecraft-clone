#include "world/world.hpp"
#include <iostream>

World::World() : tree(World::SIDE)
{
    std::cout << "World created" << std::endl;
}

void World::placeBlock(int x, int y, int z, Cube::Type t)
{
    tree.insert(x, y, z, new Cube(t));
}

void World::removeBlock(int x, int y, int z)
{
    tree.remove(x, y, z);
}

void World::buffer(Buffers &buffers)
{
    Shape sh = tree.getShape();
    std::cout << sh << std::endl;
    sh.buffer(buffers);
}