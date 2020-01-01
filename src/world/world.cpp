#include "world/world.hpp"
#include <iostream>

World::World() : chunk(0, 0, 0)
{
    std::cout << "World created" << std::endl;
}

void World::placeBlock(int x, int y, int z, Cube::Type t)
{
    Cube *c = new Cube(t);
    chunk.placeAt(x, y, z, c);
}

void World::buffer(Buffers& buffers)
{
    Shape sh = chunk.getGeometry();
    sh.buffer(buffers);
}