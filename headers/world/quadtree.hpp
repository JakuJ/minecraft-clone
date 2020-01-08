#pragma once

#include "world/chunk.hpp"
#include "world/chunk_sector.hpp"
#include <functional>
#include "utility/timing.hpp"

struct Node {
    unsigned int level;
    int x0, z0;

    explicit Node(unsigned int level);

    Node(unsigned int level, int x0, int z0);

    virtual ~Node() = default;

    [[nodiscard]] unsigned int getExtent() const;
};

struct Branch : public Node {
    Node *q1, *q2, *q3, *q4;

    explicit Branch(unsigned int level);

    Branch(unsigned int level, int x0, int z0);

    ~Branch() override;

    Node *makeChild(int x, int z);

    Node *descent(int x, int z);
};

struct Leaf : public Node {
    Chunk chunk;

    Leaf(int x0, int z0);

    template<typename T>
    T getBy(std::function<T(const Chunk &)>) const;
};

template<typename T>
T Leaf::getBy(std::function<T(const Chunk &)> f) const {
    return f(chunk);
}

class QuadTree {
    Branch root;

    Leaf *leafAt(int x, int z);

public:
    explicit QuadTree(unsigned int depth);

    void insert(int x, int y, int z, Block *);

    void remove(int x, int y, int z);

    int chunkIDAt(int x, int z);

    // Mesh generation
    ChunkSector getSurrounding(int x, int z, int radius);
};
