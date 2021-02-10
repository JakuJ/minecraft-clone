#pragma once

#include <functional>
#include <glm/detail/type_vec3.hpp>
#include <glm/vec3.hpp>
#include "world/Chunk.hpp"
#include "world/ChunkSector.hpp"
#include "utils/timers.hpp"

/// Represents a node in a quad tree.
struct Node {
    /// The level at which this node is present in the tree (0 for leaves).
    int level;

    int x0, z0;

    explicit Node(int level);

    Node(int level, int x0, int z0);

    virtual ~Node() = default;

    /// Get the side length of the represented area.
    [[nodiscard]] double getExtent() const;
};

/// A non-leaf node in a quad tree.
class Branch : public Node {
    Node *q1;
    Node *q2;
    Node *q3;
    Node *q4;

    /// Allocate a new node at the specific coordinates.
    Node *makeChild(int x, int z);

public:
    explicit Branch(int level);

    Branch(int level, int x0, int z0);

    ~Branch() override;

    /// Return the child node that corresponds to the provided coordinates.
    /// Creates the node lazily if not present.
    Node *descent(int x, int z);
};

/// A leaf node in the quad tree. Stores a chunk.
struct Leaf : public Node {
    /// The chunk stored in the leaf node.
    Chunk chunk;

    Leaf(int x0, int z0);
};

/// Represents a quad tree. Used for efficient querying of chunk data.
class QuadTree {
    /// Root node of the tree.
    Branch root;

    /// Return the leaf corresponding to the specific coordinate.
    Leaf *leafAt(int x, int z);

public:
    explicit QuadTree(int depth);

    /// Add a block at a specific location.
    void insert(int x, int y, int z, Block *);

    /// Remove a block at a specific location.
    void remove(int x, int y, int z);

    /// Return the chunk corresponding to the specific coordinate.
    Chunk *chunkAt(int x, int z);

    /// Get the surrounding chunk sector
    ChunkSector getSurrounding(int x, int z, int radius);
};
