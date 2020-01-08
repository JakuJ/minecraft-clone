#pragma once

#include "world/chunk.hpp"
#include "rendering/mesh.hpp"

class ChunkSector {
    const int side;
    Chunk ***chunks;

public:
    ChunkSector(Chunk ***chunks, int side);

    ~ChunkSector();

    [[nodiscard]] Block *getAt(int x, int y, int z) const;

    [[nodiscard]] QuadMesh getQuadMesh() const;

    [[nodiscard]] InstanceMesh getInstanceMesh() const;
};