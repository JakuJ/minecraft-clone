#pragma once

#include <string>
#include <thread>
#include <atomic>

#include "buffers/buffers.hpp"
#include "world/chunk.hpp"
#include "rendering/program.hpp"
#include "rendering/texture.hpp"
#include "rendering/mesh.hpp"
#include "world/world.hpp"
#include "player/player.hpp"

class Renderer
{
protected:
    size_t buffered_size;
    std::atomic<bool> new_data;
    std::mutex data_mutex;

    Renderer(const std::string &, const std::string &);

public:
    Texture2D texture;
    Program program;

    virtual void render(World &, Player &) = 0;
    virtual void bufferMesh() = 0;
};

class QuadRenderer : public Renderer
{
    QuadBuffers buffers;

    void preloadMesh(const QuadMesh &);
    void bufferMesh() override;

public:
    QuadRenderer();

    void render(World &, Player &) override;
};

class InstanceRenderer : public Renderer
{
    InstanceBuffers buffers;
    size_t buffered_instances;

    void preloadMesh(const InstanceMesh &);
    void bufferMesh() override;

public:
    InstanceRenderer();

    void render(World &, Player &) override;
};