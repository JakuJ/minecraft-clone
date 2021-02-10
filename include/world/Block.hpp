#pragma once

#include <iostream>
#include <array>
#include <utility>
#include "utils/enums.hpp"

/// A type alias for an array that holds 12 floats.
/// Used for passing four 3D vertices when rendering block faces.
using arr_t = std::array<float, 12>;

/// Represents a single block in the game world.
struct Block {
public:
    /// An enumeration of block faces.
    enum Face {
        UP = 0,
        DOWN,
        BACK,
        FRONT,
        RIGHT,
        LEFT,
        FACES ///< Enum size
    };

    /// An enumeration of block types.
    enum Type {
        BEDROCK = 0,
        STONE,
        DIRT,
        GRASS,
        ACACIA_LOG,
        ACACIA_LEAVES,
        WATER,
        SAND,
        TYPES ///< Enum size
    };

    /// Generate geometry for a given block face (vertices' coordinates and normal vectors).
    /// \return A pair of vectors – vertices and normals.
    [[nodiscard]] static std::pair<arr_t, arr_t> getFace(Block::Face face);

private:
    /// Allows for a quick lookup of whether a block type has transparency.
    static const bool transparency_table[TYPES];

    /// Allows for a quick lookup of whether a block type is solid or not.
    static const bool solidity_table[TYPES];

public:
    /// Type of the block.
    Type type;

    explicit Block(Type);

    /// Check whether this block has transparency.
    [[nodiscard]] bool isTransparent() const;

    /// Check whether this block is solid.
    [[nodiscard]] bool isSolid() const;

    friend std::ostream &operator<<(std::ostream &, const Block &);
};

GENERATE_ENUM_OPERATORS(Block::Face)