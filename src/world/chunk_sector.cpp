#include "world/chunk_sector.hpp"
#include "utils/timing.hpp"

ChunkSector::ChunkSector(std::vector<Chunk *> chunks, int side)
        : side(side), chunks(std::move(chunks)) {}

 auto &ChunkSector::at(int x, int z) const {
     return chunks[x + side * z];
 }

Block *ChunkSector::getAt(int x, int y, int z) const {
    if (x < 0 || y < 0 || z < 0) {
        return nullptr;
    }

    int cx = x / Chunk::SIDE;
    int cz = z / Chunk::SIDE;

    if (cx < 0 || cx >= side || cz < 0 || cz >= side) {
        return nullptr;
    }

    return at(cx, cz)->getAt(x - cx * Chunk::SIDE, y, z - cz * Chunk::SIDE);
}

QuadMesh ChunkSector::getQuadMesh() const {
    MeanScopedTimer timer("ChunkSector::getQuadMesh");

    QuadMesh opaque, transparent;

    int x0 = at(0, 0)->x0;
    int z0 = at(0, 0)->z0;

    for (int x = 0; x < side * static_cast<int>(Chunk::SIDE); x++) {
        for (int y = 0; y < static_cast<int>(Chunk::HEIGHT); y++) {
            for (int z = 0; z < side * static_cast<int>(Chunk::SIDE); z++) {
                Block *block = getAt(x, y, z);

                if (block) {
                    Block *up = getAt(x, y + 1, z);
                    Block *down = getAt(x, y - 1, z);
                    Block *north = getAt(x, y, z + 1);
                    Block *south = getAt(x, y, z - 1);
                    Block *east = getAt(x + 1, y, z);
                    Block *west = getAt(x - 1, y, z);

                    Block *faces[]{up, down, north, south, east, west};

                    // Only render visible faces
                    for (auto face = (Block::Face) 0; face < Block::FACES; face++) {
                        if (!faces[face] ||
                            (faces[face]->type != block->type && Block::transparency_table[faces[face]->type])) {
                            auto[vectors, normals] = block->getFace(face);

                            for (int j = 0; j <= 9; j += 3) {
                                vectors[j] += static_cast<float>(x + x0);
                                vectors[j + 1] += static_cast<float>(y);
                                vectors[j + 2] += static_cast<float>(z + z0);
                            }

                            if (Block::transparency_table[block->type]) {
                                transparent.addQuad(vectors, normals, block->type, face);
                            } else {
                                opaque.addQuad(vectors, normals, block->type, face);
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

InstanceMesh ChunkSector::getInstanceMesh() const {
    MeanScopedTimer timer("ChunkSector::getInstanceMesh");

    InstanceMesh opaque, transparent;

    int x0 = at(0, 0)->x0;
    int z0 = at(0, 0)->z0;

    for (int x = 0; x < side * static_cast<int>(Chunk::SIDE); x++) {
        for (int y = 0; y < static_cast<int>(Chunk::HEIGHT); y++) {
            for (int z = 0; z < side * static_cast<int>(Chunk::SIDE); z++) {
                Block *block = getAt(x, y, z);
                if (block) {
                    Block *up = getAt(x, y + 1, z);
                    Block *down = getAt(x, y - 1, z);
                    Block *north = getAt(x, y, z + 1);
                    Block *south = getAt(x, y, z - 1);
                    Block *east = getAt(x + 1, y, z);
                    Block *west = getAt(x - 1, y, z);

                    Block *faces[]{up, down, north, south, east, west};

                    for (auto face = (Block::Face) 0; face < Block::FACES; face++) {
                        if (!faces[face] ||
                            (faces[face]->type != block->type && Block::transparency_table[faces[face]->type])) {
                            if (Block::transparency_table[block->type]) {
                                transparent.addCube(x + x0, y, z + z0, block->type, face);
                            } else {
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

