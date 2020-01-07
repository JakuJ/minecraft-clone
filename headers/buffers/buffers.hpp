#pragma once

#include "buffers/BufferObjects.hpp"
#include "rendering/mesh.hpp"

class Buffers
{
protected:
    VBO<float, 3> vertices;
    VBO<float, 2> texCoords;

    Buffers();

public:
    virtual size_t size() const = 0;

    virtual void clear();
    virtual void bufferData();
};

class QuadBuffers : public Buffers
{
    EBO indices;

public:
    QuadBuffers();

    size_t size() const override;
    virtual void clear() override;
    virtual void bufferData() override;

    void bufferMesh(const QuadMesh &);
};

class InstanceBuffers : public Buffers
{
    VBO<float, 3> offsets;
    VBO<float, 3> typeInfos;

public:
    InstanceBuffers();

    size_t size() const override;
    size_t instances() const;

    void clear() override;
    void bufferData() override;
    void bufferMesh(const InstanceMesh &);
};
