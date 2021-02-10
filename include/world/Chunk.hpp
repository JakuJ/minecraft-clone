#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include "world/Block.hpp"
#include "rendering/meshes.hpp"

/// Represents a single chunk of blocks.
class Chunk {
    /// An accumulator variable for generating subsequent IDs.
    static u_int NEXT_ID;

    /// A vector of blocks present in this chunk. Null pointer means no block.
    std::vector<Block *> blocks;

    /// Check whether a relative coordinate lies within this chunk.
    [[nodiscard]] bool valid(int x, int y, int z) const;

    /// Return a block at the provided relative coordinates without performing boundary checks.
    /// \return A pointer to the block at a given position.
    [[nodiscard]] Block *&unsafeAt(int x, int y, int z);

    /// Generate terrain for this chunk of space based on a seed value.
    /// \param seed The seed for this chunk.
    void generate(int seed);

public:
    /// Chunk height in blocks.
    static const int HEIGHT = 256;

    /// Side length of a chunk in blocks.
    static const int SIDE = 16;

    /// Unique chunk ID.
    u_int id;

    /// Coordinate of the most south-west block in the chunk.
    const int x0, z0;

    Chunk(int x0, int z0);

    ~Chunk();

    /// Place a block at the given relative position.
    /// Remove the block that previously occupied that space if necessary.
    /// \param block Pointer to the block to place.
    void placeAt(int x, int y, int z, Block *block);

    /// Remove a block at the given relative position.
    void removeAt(int x, int y, int z);

    /// Get the block at a relative position. Performs boundary checks.
    /// \return Pointer to the block or nullptr if not present or if the position is out of bounds.
    [[nodiscard]] Block *getAt(int x, int y, int z);
};
