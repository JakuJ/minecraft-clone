#include "rendering/renderer.hpp"
#include "utility/timing.hpp"

#include <thread>
#include <atomic>

Renderer::Renderer(const std::string &vPath, const std::string &fPath) : buffered_size(0), texture("data/textures/blocks.png", GL_TEXTURE0, true), program(vPath, fPath)
{
    // Create a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Assign a texture sampler
    program.setUniform("cubes", 0);

    // Set texturing parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

QuadRenderer::QuadRenderer() : Renderer("data/shaders/quad.vert", "data/shaders/quad.frag") {}

void QuadRenderer::render(World &world, Player &player)
{
    static std::atomic<bool> newData = false;
    static std::mutex mutex;

    float px = player.camera.position[0];
    float pz = player.camera.position[2];

    int currentID = world.tree.chunkIDAt(px, pz);

    if (player.chunkID != currentID)
    {
        std::cout << "Moving from chunk " << player.chunkID << " to " << currentID << std::endl;
        player.chunkID = currentID;

        std::thread thread([&](float x, float z) {
            std::lock_guard<std::mutex> guard(mutex);

            MeanScopedTimer("Mesh preloading");
            QuadMesh mesh = world.tree.getSurrounding<QuadMesh>(x, z, 3);
            std::cout << mesh << std::endl;
            preloadMesh(mesh);

            newData = true;
        },
                           px, pz);

        thread.detach();
    }

    if (newData)
    {
        MeanScopedTimer("Buffering to GPU");
        bufferMesh();
        newData = false;
    }

    program.use();
    texture.use();

    program.setUniform("mvp", player.camera.getViewMatrix());

    glDrawElements(GL_TRIANGLES, buffered_size, GL_UNSIGNED_INT, 0);
}

void QuadRenderer::preloadMesh(const QuadMesh &mesh)
{
    buffers.clear();
    buffers.bufferMesh(mesh);
}

void QuadRenderer::bufferMesh()
{
    buffers.bufferData();
    buffered_size = buffers.size();
}

InstanceRenderer::InstanceRenderer() : Renderer("data/shaders/instance.vert", "data/shaders/quad.frag"), buffered_instances(0)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);
}

void InstanceRenderer::preloadMesh(const InstanceMesh &mesh)
{
    buffers.clear();
    buffers.bufferMesh(mesh);
}

void InstanceRenderer::bufferMesh()
{
    buffers.bufferData();
    buffered_size = buffers.size();
    buffered_instances = buffers.instances();
}

void InstanceRenderer::render(World &world, Player &player)
{
    static std::atomic<bool> newData = false;
    static std::mutex mutex;

    float px = player.camera.position[0];
    float pz = player.camera.position[2];

    int currentID = world.tree.chunkIDAt(px, pz);

    if (player.chunkID != currentID)
    {
        std::cout << "Moving from chunk " << player.chunkID << " to " << currentID << std::endl;
        player.chunkID = currentID;

        std::thread thread([this, &world](float x, float z) {
            std::lock_guard<std::mutex> guard(mutex);

            MeanScopedTimer("Mesh preloading");
            InstanceMesh mesh = world.tree.getSurrounding<InstanceMesh>(x, z, 3);
            std::cout << mesh << std::endl;
            preloadMesh(mesh);

            newData = true;
        },
                           px, pz);

        thread.detach();
    }

    if (newData)
    {
        MeanScopedTimer("Buffering to GPU");
        bufferMesh();
        newData = false;
    }

    program.use();
    texture.use();

    program.setUniform("mvp", player.camera.getViewMatrix());

    glDrawArraysInstanced(GL_TRIANGLES, 0, buffered_size, buffered_instances);
}