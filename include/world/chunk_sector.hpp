#pragma once

#include <vector>
#include "world/chunk.hpp"
#include "rendering/mesh.hpp"

class ChunkSector {
    const int side;
    std::vector<Chunk *> chunks;

    [[nodiscard]] auto &at(int x, int z) const;

public:
    ChunkSector(std::vector<Chunk *> chunks, int side);

    [[nodiscard]] Block *getAt(int x, int y, int z) const;

    [[nodiscard]] QuadMesh getQuadMesh() const;

    [[nodiscard]] InstanceMesh getInstanceMesh() const;
};
