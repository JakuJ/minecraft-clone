#pragma once

#include "world/chunk.hpp"

struct Node
{
    unsigned int level;
    int x0, z0;

    Node(unsigned int level);
    Node(unsigned int level, int x0, int z0);
    virtual ~Node() = 0;

    unsigned int getExtent() const;
    virtual Shape getShape() const = 0;
};

struct Branch : public Node
{
    Node *q1, *q2, *q3, *q4;

    Branch(unsigned int level);
    Branch(unsigned int level, int x0, int z0);
    ~Branch();

    Node *makeChild(int x, int z);
    Node *descent(int x, int z);

    Shape getShape() const override;
};

struct Leaf : public Node
{
    Chunk chunk;
    Leaf(int x0, int z0);

    Shape getShape() const override;
};

class QuadTree
{
    Branch root;
    Leaf *leafAt(int x, int z);

public:
    QuadTree(unsigned int depth);

    void insert(int x, int y, int z, Block *);
    void remove(int x, int y, int z);
    Shape getShape() const;
};