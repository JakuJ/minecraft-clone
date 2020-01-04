#pragma once

#include <iostream>
#include <functional>
#include "world/block.hpp"
#include "rendering/mesh.hpp"
#include <utility>
class Chunk
{
    static const u_int HEIGHT = 256;
    static u_int NEXT_ID;
    
    Block ****blocks;

    const int x0, z0;

    void for_each(std::function<void(int, int, int, Block *)>) const;

public:
    static const u_int SIDE = 16;

    u_int id;

    Chunk(int x0, int z0);
    ~Chunk();

    void placeAt(u_int, u_int, u_int, Block *);
    void removeAt(u_int, u_int, u_int);

    Block *getAt(int x, int y, int z) const;
    std::pair<Mesh, Mesh> getMeshes(float x_off, float z_off) const;

    void generate(int seed);

    friend std::ostream &operator<<(std::ostream &, const Chunk &);
};