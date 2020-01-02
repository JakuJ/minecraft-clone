#pragma once

#include <vector>
#include "buffers/buffers.hpp"
#include "world/block.hpp"

struct Mesh
{
    std::vector<float> vertices;
    std::vector<u_int> indices;
    std::vector<float> texCoords;

    Mesh();

    void addQuad(const std::vector<float> &vs, Block::Type texId, Block::Face faceId);
    void buffer(QuadBuffers &) const;
    void translate(float x, float y, float z);

    // Operators
    void operator+=(const Mesh &other);

    friend std::ostream &operator<<(std::ostream &out, const Mesh &mesh);
};