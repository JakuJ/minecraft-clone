#pragma once

#include <iostream>
#include <vector>
#include "enums.hpp"

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
        WEST,
        FACES // enum size
    };

    enum Type
    {
        BEDROCK = 0,
        STONE,
        DIRT,
        GRASS,
        ACACIA_LOG,
        ACACIA_LEAVES,
        WATER,
        SAND,
        TYPES // enum size
    };

    static const bool transparency_table[TYPES];

    Type type;

    Block(Type);

    std::vector<float> getFace(Block::Face) const;

    friend std::ostream &operator<<(std::ostream &, const Block &);
};

GENERATE_ENUM_OPERATORS(Block::Type)
GENERATE_ENUM_OPERATORS(Block::Face)