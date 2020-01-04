#include <iostream>
#include <thread>
#include <atomic>

#include "world/world.hpp"
#include "utility/timing.hpp"

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

            MeanScopedTimer("Mesh preloading", 0);
            QuadMesh mesh = tree.getSurrounding<QuadMesh>(x, z, 6);
            std::cout << mesh << std::endl;
            renderer.preloadMesh(mesh);

            newData = true;
        },
                           px, pz);

        thread.detach();
    }

    if (newData)
    {
        MeanScopedTimer("Buffering to GPU", 1);
        renderer.bufferMesh();
        newData = false;
    }

    renderer.program.setUniform("mvp", player.camera.getViewMatrix());
    renderer.render();
}