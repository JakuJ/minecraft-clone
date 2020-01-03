#include "world/world.hpp"
#include <iostream>

World::World() : tree(World::SIDE)
{
    std::cout << "World created" << std::endl;
}

void World::placeBlock(int x, int y, int z, Block::Type t)
{
    tree.insert(x, y, z, new Block(t));
}

void World::removeBlock(int x, int y, int z)
{
    tree.remove(x, y, z);
}

void World::sendData(float x, float z)
{
    Mesh mesh = tree.getSurrounding(x, z, 1);
    std::cout << mesh << std::endl;

    renderer.bufferMesh(mesh);
}

void World::update(Player &player)
{
    float x = player.camera.position[0];
    float z = player.camera.position[2];

    int currentID = tree.chunkIDAt(x, z);
    
    if(player.chunkID != currentID)
    {
        std::cout << "Moving from chunk " << currentID << " to " << player.chunkID << std::endl;
        player.chunkID = currentID;
        sendData(x, z);
    }
    
    renderer.program.setUniform("mvp", player.camera.getViewMatrix());
    renderer.render();
}