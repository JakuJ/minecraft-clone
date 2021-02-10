#pragma once

#include <vector>
#include "world/Block.hpp"

/// Represents a mesh of blocks. Used with the QuadRenderer.
struct QuadMesh {
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<u_int> indices;
    std::vector<float> texCoords;

    /// Add a quad to the mesh.
    /// \param vs An array of vertex coordinates.
    /// \param ns An array of normal vector coordinates.
    /// \param texId Type of the block this quad belongs to.
    /// \param faceId ID of the face this quad represents in a block.
    void addQuad(const arr_t &vs, const arr_t &ns, Block::Type texId, Block::Face faceId);

    /// Merge two meshes together.
    void operator+=(const QuadMesh &other);
};

/// Represents a mesh of blocks. Used with the InstancingRenderer.
struct InstanceMesh {
    std::vector<float> offsets;
    std::vector<float> typeInfos;

    /// Add a cube to the mesh.
    /// \param texId Type of the block this quad belongs to.
    /// \param faceId ID of the face this quad represents in a block.
    void addCube(float x, float y, float z, Block::Type texId, Block::Face faceId);

    /// Merge two meshes together.
    void operator+=(const InstanceMesh &other);

    friend std::ostream &operator<<(std::ostream &out, const InstanceMesh &mesh);
};
