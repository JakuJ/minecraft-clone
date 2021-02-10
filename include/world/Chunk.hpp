#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include "world/Block.hpp"
#include "rendering/meshes.hpp"

class Chunk {
    static const int HEIGHT = 256;
    static u_int NEXT_ID;

    std::vector<Block *> blocks;

    [[nodiscard]] bool valid(int, int, int) const;

    [[nodiscard]] Block *&unsafeAt(int, int, int);

public:
    static const int SIDE = 16;

    u_int id;
    const int x0, z0;

    Chunk(int x0, int z0);

    ~Chunk();

    void placeAt(int x, int y, int z, Block *block);

    void removeAt(int x, int y, int z);

    [[nodiscard]] Block *getAt(int x, int y, int z);

    void generate(int seed);

    friend class ChunkSector;
};
