#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include "utils/enums.hpp"

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

private:
    static const bool transparency_table[TYPES];
    static const bool solidity_table[TYPES];

public:

    Type type;

    explicit Block(Type);

    [[nodiscard]] std::pair<std::vector<float>, std::vector<float>> getFace(Block::Face) const;

    friend std::ostream &operator<<(std::ostream &, const Block &);

    [[nodiscard]] bool isTransparent() const;

    [[nodiscard]] bool isSolid() const;
};

GENERATE_ENUM_OPERATORS(Block::Face)