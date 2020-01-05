#include "world/chunk_sector.hpp"
#include "utility/timing.hpp"

ChunkSector::ChunkSector(Chunk ***chunks, int side)
    : side(side), chunks(chunks) {}

ChunkSector::~ChunkSector()
{
    for (int i = 0; i < side; i++)
    {
        delete[] chunks[i];
    }
    delete[] chunks;
}

Block *ChunkSector::getAt(int x, int y, int z) const
{
    if (x < 0 || y < 0 || z < 0)
    {
        return nullptr;
    }

    int cx = x / (int)Chunk::SIDE;
    int cz = z / (int)Chunk::SIDE;

    if (cx < 0 || cx >= side || cz < 0 || cz >= side)
    {
        return nullptr;
    }

    return chunks[cx][cz]->getAt(x - cx * Chunk::SIDE, y, z - cz * Chunk::SIDE);
}

QuadMesh ChunkSector::getQuadMesh() const
{
    MeanScopedTimer timer("ChunkSector::getQuadMesh");

    QuadMesh opaque, transparent;

    int x0 = chunks[0][0]->x0;
    int z0 = chunks[0][0]->z0;

    for (int x = 0; x < side * (int)Chunk::SIDE; x++)
    {
        for (int y = 0; y < (int)Chunk::HEIGHT; y++)
        {
            for (int z = 0; z < side * (int)Chunk::SIDE; z++)
            {
                Block *block = getAt(x, y, z);

                if (block)
                {
                    Block *up = getAt(x, y + 1, z);
                    Block *down = getAt(x, y - 1, z);
                    Block *north = getAt(x, y, z + 1);
                    Block *south = getAt(x, y, z - 1);
                    Block *east = getAt(x + 1, y, z);
                    Block *west = getAt(x - 1, y, z);

                    Block *faces[]{up, down, north, south, east, west};

                    // Only render visible faces
                    for (Block::Face face = (Block::Face)0; face < Block::FACES; face++)
                    {
                        if (!faces[face] || (faces[face]->type != block->type && Block::transparency_table[faces[face]->type]))
                        {
                            std::vector<float> vecs = block->getFace(face);
                            for (int j = 0; j <= 9; j += 3)
                            {
                                vecs[j] += x + x0;
                                vecs[j + 1] += y;
                                vecs[j + 2] += z + z0;
                            }

                            if (Block::transparency_table[block->type])
                            {
                                transparent.addQuad(vecs, block->type, face);
                            }
                            else
                            {
                                opaque.addQuad(vecs, block->type, face);
                            }
                        }
                    }
                }
            }
        }
    }

    opaque += transparent;

    return opaque;
}

InstanceMesh ChunkSector::getInstanceMesh() const
{
    MeanScopedTimer timer("ChunkSector::getInstanceMesh");

    InstanceMesh opaque, transparent;

    int x0 = chunks[0][0]->x0;
    int z0 = chunks[0][0]->z0;

    for (int x = 0; x < side * (int)Chunk::SIDE; x++)
    {
        for (int y = 0; y < (int)Chunk::HEIGHT; y++)
        {
            for (int z = 0; z < side * (int)Chunk::SIDE; z++)
            {
                Block *block = getAt(x, y, z);
                if (block)
                {
                    Block *up = getAt(x, y + 1, z);
                    Block *down = getAt(x, y - 1, z);
                    Block *north = getAt(x, y, z + 1);
                    Block *south = getAt(x, y, z - 1);
                    Block *east = getAt(x + 1, y, z);
                    Block *west = getAt(x - 1, y, z);

                    Block *faces[]{up, down, north, south, east, west};

                    for (Block::Face face = (Block::Face)0; face < Block::FACES; face++)
                    {
                        if (!faces[face] || (faces[face]->type != block->type && Block::transparency_table[faces[face]->type]))
                        {
                            if (Block::transparency_table[block->type])
                            {
                                transparent.addCube(x + x0, y, z + z0, block->type, face);
                            }
                            else
                            {
                                opaque.addCube(x + x0, y, z + z0, block->type, face);
                            }
                        }
                    }
                }
            }
        }
    }

    opaque += transparent;

    return opaque;
}