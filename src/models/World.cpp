#include "models/World.hpp"

World::World() : tree(World::SIDE) {}

void World::placeBlock(int x, int y, int z, Block::Type t) {
    tree.insert(x, y, z, new Block(t));
}

void World::removeBlock(int x, int y, int z) {
    tree.remove(x, y, z);
}
