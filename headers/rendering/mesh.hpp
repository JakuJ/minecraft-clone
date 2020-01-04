#pragma once

#include <vector>
#include "world/block.hpp"

struct Mesh
{
    std::vector<float> vertices;
    std::vector<u_int> indices;
    std::vector<float> offsets;
    std::vector<float> texCoords;

    void addQuad(const std::vector<float> &vs, Block::Type texId, Block::Face faceId);
    void addCube(float x, float y, float z, Block::Type texId);

    // Operators
    void operator+=(const Mesh &other);

    friend std::ostream &operator<<(std::ostream &out, const Mesh &mesh);
};