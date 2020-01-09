#pragma once

#include <functional>
#include "world/chunk.hpp"
#include "world/chunk_sector.hpp"
#include "utils/timing.hpp"

struct Node {
    int level;
    int x0, z0;

    explicit Node(int level);

    Node(int level, int x0, int z0);

    virtual ~Node() = default;

    [[nodiscard]] double getExtent() const;
};

struct Branch : public Node {
    Node *q1, *q2, *q3, *q4;

    explicit Branch(int level);

    Branch(int level, int x0, int z0);

    ~Branch() override;

    Node *makeChild(int x, int z);

    Node *descent(int x, int z);
};

struct Leaf : public Node {
    Chunk chunk;

    Leaf(int x0, int z0);

};

class QuadTree {
    Branch root;

    Leaf *leafAt(int x, int z);

public:
    explicit QuadTree(int depth);

    void insert(int x, int y, int z, Block *);

    void remove(int x, int y, int z);

    int chunkIDAt(int x, int z);

    // Mesh generation
    ChunkSector getSurrounding(int x, int z, int radius);
};
