#pragma once

#include <string>

#include "buffers/buffers.hpp"
#include "world/chunk.hpp"
#include "rendering/program.hpp"
#include "rendering/texture.hpp"
#include "rendering/mesh.hpp"

class Renderer
{
public:
    virtual void render() = 0;
};

class QuadRenderer : public Renderer
{
    Texture2D texture;
    QuadBuffers buffers;
    u_int size;

public:
    Program program;
    
    QuadRenderer();
    void bufferMesh(const Mesh &);
    void render() override;
};