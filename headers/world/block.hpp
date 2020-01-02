#pragma once

#include <iostream>
#include <vector>

struct Block
{
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
    };

    static const u_int TYPES = 2;

    Type type;

    Block(Type);

    std::vector<float> getFace(Block::Face) const;

    friend std::ostream &operator<<(std::ostream &, const Block &);
};