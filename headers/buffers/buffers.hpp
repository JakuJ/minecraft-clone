#pragma once

#include "rendering/mesh.hpp"
#include "buffers/VBO.hpp"
#include "buffers/EBO.hpp"

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
    virtual void bufferData() const;
    virtual void bufferMesh(const Mesh&) = 0;
};

class QuadBuffers : public Buffers
{
public:
    QuadBuffers();
    
    virtual void bufferMesh(const Mesh&) override;
};

class InstanceBuffers : public Buffers
{
    VBO<float, 4> offsets;

public:
    InstanceBuffers();
    
    size_t instances() const;

    void clear() override;
    void bufferData() const override;
    virtual void bufferMesh(const Mesh&) override;
};