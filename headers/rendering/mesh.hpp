#pragma once

#include <vector>
#include "world/block.hpp"

struct QuadMesh
{
    std::vector<float> vertices;
    std::vector<u_int> indices;
    std::vector<float> texCoords;

    void addQuad(const std::vector<float> &vs, Block::Type texId, Block::Face faceId);
    
    virtual void operator+=(const QuadMesh &other);
    friend std::ostream &operator<<(std::ostream &out, const QuadMesh &mesh);
};

struct InstanceMesh
{
    std::vector<float> offsets;

    virtual void operator+=(const InstanceMesh &other);
    void addCube(float x, float y, float z, Block::Type texId);
};