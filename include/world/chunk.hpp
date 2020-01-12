#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include "world/block.hpp"
#include "rendering/mesh.hpp"

class Chunk {
    static const int HEIGHT = 256;
    static u_int NEXT_ID;

    const int x0, z0;

    std::vector<Block *> blocks;

    [[nodiscard]] auto &at(int, int, int);

public:
    static const int SIDE = 16;

    u_int id;

    Chunk(int x0, int z0);

    ~Chunk();

    void placeAt(int x, int y, int z, Block *block);

    void removeAt(int x, int y, int z);

    [[nodiscard]] Block *getAt(int x, int y, int z);

    void generate(int seed);

    friend class ChunkSector;
};
