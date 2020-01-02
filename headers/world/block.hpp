#pragma once

#include <iostream>
#include <vector>

struct Block
{
public:
    enum Face
    {
        UP = 0,
        DOWN,
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    static const u_int FACES = 6;

    enum Type
    {
        DIRT = 0,
        GRASS,
        COBBLESTONE,
        STONE,
        ACACIA_LOG,
        ACACIA_LEAVES
    };

    static const u_int TYPES = 6;

    Type type;

    Block(Type);

    std::vector<float> getFace(Block::Face) const;

    friend std::ostream &operator<<(std::ostream &, const Block &);
};