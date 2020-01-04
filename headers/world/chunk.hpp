#pragma once

#include <iostream>
#include <functional>
#include "world/block.hpp"
#include "rendering/mesh.hpp"
class Chunk
{
    static const u_int HEIGHT = 256;
    static const u_int BEDROCK_LEVEL = 5;
    static u_int NEXT_ID;
    
    Block ****blocks;

    void for_each(std::function<void(int, int, int, Block *)>) const;

public:
    static const u_int SIDE = 16;
    static const u_int SEA_LEVEL = 64;

    u_int id;

    Chunk();
    ~Chunk();

    void placeAt(u_int, u_int, u_int, Block *);
    void removeAt(u_int, u_int, u_int);

    Block *getAt(int x, int y, int z) const;
    Mesh getMesh(float x_off, float z_off) const;

    void generate(int seed);

    friend std::ostream &operator<<(std::ostream &, const Chunk &);
};