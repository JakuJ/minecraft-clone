#pragma once

#include <iostream>
#include <functional>
#include <utility>
#include "world/block.hpp"
#include "rendering/mesh.hpp"

class Chunk {
    static const u_int HEIGHT = 256;
    static u_int NEXT_ID;

    Block ****blocks;

    const int x0, z0;

    void for_each(const std::function<void(int, int, int, Block *)> &) const;

public:
    static const u_int SIDE = 16;

    u_int id;

    Chunk(int x0, int z0);

    ~Chunk();

    void placeAt(u_int, u_int, u_int, Block *);

    void removeAt(u_int, u_int, u_int);

    [[nodiscard]] Block *getAt(int x, int y, int z) const;

    void generate(int seed);

    friend class ChunkSector;

    friend std::ostream &operator<<(std::ostream &, const Chunk &);
};
