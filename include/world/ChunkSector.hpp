#pragma once

#include <vector>
#include "world/Chunk.hpp"
#include "rendering/meshes.hpp"

/// Represents a square of chunks.
/// Used for creating meshes that span a number of chunks in a radius around the player.
class ChunkSector {
    /// Chunk square side length in chunks.
    const int side;

    std::vector<Chunk *> chunks;

    /// \return The chunk at the given position in the square.
    [[nodiscard]] Chunk *at(int x, int z) const;

public:
    /// Creates a new instance of the ChunkSector class.
    /// \param chunks A vector of chunks that this sector represents.
    /// \param side Chunk square side length.
    ChunkSector(std::vector<Chunk *> chunks, int side);

    /// Get the block at a given coordinate, where
    /// (0, 0, 0) is the origin (bottom-left corner) of the chunk sector.
    /// \return A pointer to the block at the provided coordinate.
    [[nodiscard]] Block *getAt(int x, int y, int z) const;

    /// Create a mesh compatible with the QuadRenderer.
    /// \return An instance of the QuadMesh class.
    [[nodiscard]] QuadMesh getQuadMesh() const;

    /// Create a mesh compatible with the InstancingRenderer.
    /// \return An instance of the InstanceMesh class.
    [[nodiscard]] InstanceMesh getInstanceMesh() const;
};
