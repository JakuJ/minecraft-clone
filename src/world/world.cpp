#include <iostream>
#include <thread>
#include <atomic>

#include "world/world.hpp"

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
    Mesh mesh = tree.getSurrounding(x, z, 3);
    std::cout << mesh << std::endl;

    renderer.setMesh(mesh);
}

void World::update(Player &player)
{
    static std::atomic<bool> newData = false;
    static std::mutex mutex;

    float px = player.camera.position[0];
    float pz = player.camera.position[2];

    int currentID = tree.chunkIDAt(px, pz);

    if (player.chunkID != currentID)
    {
        std::cout << "Moving from chunk " << player.chunkID << " to " << currentID << std::endl;
        player.chunkID = currentID;

        std::thread thread([this](float x, float z) {
            std::lock_guard<std::mutex> guard(mutex);
            sendData(x, z);
            newData = true;
        },
                           px, pz);

        thread.detach();
    }

    if (newData)
    {
        renderer.bufferMesh();
        newData = false;
    }

    renderer.program.setUniform("mvp", player.camera.getViewMatrix());
    renderer.render();
}