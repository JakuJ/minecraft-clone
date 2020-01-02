#pragma once

#include <iostream>
#include <functional>
#include "world/block.hpp"
#include "rendering/mesh.hpp"
class Chunk
{
    static const u_int HEIGHT = 8;
    Block ****blocks;

    void for_each(std::function<void(int, int, int, Block *)>) const;

public:
    static const u_int SIDE = 16;

    Chunk();
    ~Chunk();

    void placeAt(u_int, u_int, u_int, Block *);
    void removeAt(u_int, u_int, u_int);

    Block *getAt(int x, int y, int z) const;
    Mesh getMesh() const;

    friend std::ostream &operator<<(std::ostream &, const Chunk &);
};