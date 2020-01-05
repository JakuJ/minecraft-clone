#pragma once

#include "world/chunk.hpp"
#include "rendering/mesh.hpp"

class ChunkSector
{
    const int side;
    Chunk ***chunks;

public:
    ChunkSector(Chunk ***chunks, int side);
    ~ChunkSector();
    
    Block *getAt(int x, int y, int z) const;
    
    QuadMesh getQuadMesh() const;
    InstanceMesh getInstanceMesh() const;
};