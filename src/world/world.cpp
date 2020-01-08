#include <iostream>

#include "world/world.hpp"

World::World() : tree(World::SIDE) {
    std::cout << "World created" << std::endl;
}

void World::placeBlock(int x, int y, int z, Block::Type t) {
    tree.insert(x, y, z, new Block(t));
}

void World::removeBlock(int x, int y, int z) {
    tree.remove(x, y, z);
}
