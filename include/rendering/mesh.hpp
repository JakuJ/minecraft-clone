#pragma once

#include <vector>
#include "world/block.hpp"

struct QuadMesh {
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<u_int> indices;
    std::vector<float> texCoords;

    void addQuad(const std::vector<float> &vs, const std::vector<float> &ns, Block::Type texId, Block::Face faceId);

    void operator+=(const QuadMesh &other);
};

struct InstanceMesh {
    std::vector<float> offsets;
    std::vector<float> typeInfos;

    void addCube(float x, float y, float z, Block::Type texId, Block::Face faceId);

    void operator+=(const InstanceMesh &other);

    friend std::ostream &operator<<(std::ostream &out, const InstanceMesh &mesh);
};
