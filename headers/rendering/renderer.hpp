#pragma once

#include <string>

#include "buffers/buffers.hpp"
#include "world/chunk.hpp"
#include "rendering/program.hpp"
#include "rendering/texture.hpp"
#include "rendering/mesh.hpp"

class Renderer
{
protected:
    size_t buffered_size;

    Renderer(const std::string&, const std::string&);

public:
    Texture2D texture;
    Program program;

    virtual void render() = 0;
    virtual void preloadMesh(const Mesh&) = 0;
    virtual void bufferMesh() = 0;
};

class QuadRenderer : public Renderer
{
    QuadBuffers buffers;
    
public:
    QuadRenderer();

    void preloadMesh(const Mesh &) override;
    void bufferMesh() override;
    void render() override;
};

class InstanceRenderer : public Renderer
{
    InstanceBuffers buffers;
    size_t buffered_instances;

public:
    InstanceRenderer();

    void preloadMesh(const Mesh &) override;
    void bufferMesh() override;
    void render() override;
};