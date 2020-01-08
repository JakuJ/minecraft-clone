#pragma once

#include <iostream>
#include <vector>
#include "utility/enums.hpp"

struct Block {
public:
    enum Face {
        UP = 0,
        DOWN,
        BACK,
        FRONT,
        RIGHT,
        LEFT,
        FACES  // enum size
    };

    enum Type {
        BEDROCK = 0,
        STONE,
        DIRT,
        GRASS,
        ACACIA_LOG,
        ACACIA_LEAVES,
        WATER,
        SAND,
        TYPES  // enum size
    };

    static const bool transparency_table[TYPES];

    Type type;

    explicit Block(Type);

    [[nodiscard]] std::vector<float> getFace(Block::Face) const;

    friend std::ostream &operator<<(std::ostream &, const Block &);
};

GENERATE_ENUM_OPERATORS(Block::Face)