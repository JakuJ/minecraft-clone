#pragma once

#include "buffers/BufferObjects.hpp"
#include "rendering/mesh.hpp"

class Buffers
{
protected:
    VBO<float, 3> vertices;
    VBO<float, 2> texCoords;
    EBO indices;

    Buffers();

public:
    size_t size() const;

    virtual void clear();
    virtual void bufferData();
};

class QuadBuffers : public Buffers
{
public:
    QuadBuffers();

    void bufferMesh(const QuadMesh &);
};

class InstanceBuffers : public Buffers
{
    VBO<float, 4> offsets;

public:
    InstanceBuffers();

    size_t instances() const;

    void clear() override;
    void bufferData() override;
    void bufferMesh(const InstanceMesh &);
};