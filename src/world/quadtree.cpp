#include "world/quadtree.hpp"
#include <math.h>

#pragma region Node

Node::Node(unsigned int level) : level(level)
{
    int coord = getExtent() / 2;
    x0 = -coord;
    z0 = -coord;
}

Node::Node(unsigned int level, int x0, int z0) : level(level), x0(x0), z0(z0) {}

Node::~Node() {}

unsigned int Node::getExtent() const
{
    return pow(2, level) * Chunk::SIDE;
}

#pragma endregion Node

#pragma region Branch

Branch::Branch(unsigned int level) : Node(level)
{
    q1 = q2 = q3 = q4 = nullptr;
    std::cout << "Branch spanning from (" << x0 << ", " << z0 << ") created" << std::endl;
}

Branch::Branch(unsigned int level, int x0, int z0) : Node(level, x0, z0)
{
    q1 = q2 = q3 = q4 = nullptr;
    std::cout << "Branch spanning from (" << x0 << ", " << z0 << ") created" << std::endl;
}

Branch::~Branch()
{
    delete q1;
    delete q2;
    delete q3;
    delete q4;
}

Node *Branch::makeChild(int x, int z)
{
    if (level > 1)
    {
        return new Branch(level - 1, x, z);
    }
    return new Leaf(x, z);
}

Node *Branch::descent(int x, int z)
{
    int width = getExtent() / 2;
    int midX = x0 + width;
    int midZ = z0 + width;

    if (x >= midX && z >= midZ)
    {
        if (!q1)
        {
            q1 = makeChild(midX, midZ);
        }
        return q1;
    }
    else if (x >= midX && z < midZ)
    {
        if (!q4)
        {
            q4 = makeChild(midX, z0);
        }
        return q4;
    }
    else if (x < midX && z >= midZ)
    {
        if (!q2)
        {
            q2 = makeChild(x0, midZ);
        }
        return q2;
    }
    else
    {
        if (!q3)
        {
            q3 = makeChild(x0, z0);
        }
        return q3;
    }
}

std::pair<QuadMesh, QuadMesh> Branch::getMeshes() const
{
    QuadMesh m1, m2;

    for (Node *q : {q1, q2, q3, q4})
    {
        if (q)
        {
            auto meshes = q->getMeshes();
            m1 += meshes.first;
            m2 += meshes.second;
        }
    }

    return std::make_pair(m1, m2);
}

#pragma endregion Branch

#pragma region Leaf

Leaf::Leaf(int x0, int z0) : Node(0, x0, z0), chunk(x0, z0)
{
    std::cout << "Leaf spanning from (" << x0 << ", " << z0 << ") created" << std::endl;
}

std::pair<QuadMesh, QuadMesh> Leaf::getMeshes() const
{
    return chunk.getMeshes(x0, z0);
}

#pragma endregion Leaf

#pragma region QuadTree

QuadTree::QuadTree(unsigned int depth) : root(depth)
{
}

Leaf *QuadTree::leafAt(int x, int z)
{
    int extent = root.getExtent() / 2;

    if (x < -extent || x >= extent || z < -extent || z >= extent)
    {
        return nullptr;
    }

    Branch *n = &root;
    while (n->level > 1)
    {
        n = (Branch *)(n->descent(x, z));
    }

    return (Leaf *)(n->descent(x, z));
}

void QuadTree::insert(int x, int y, int z, Block *block)
{
    Leaf *leaf = leafAt(x, z);
    if (leaf)
    {
        leaf->chunk.placeAt(x - leaf->x0, y, z - leaf->z0, block);
    }
}

void QuadTree::remove(int x, int y, int z)
{
    Leaf *leaf = leafAt(x, z);
    if (leaf)
    {
        leaf->chunk.removeAt(x - leaf->x0, y, z - leaf->z0);
    }
}

QuadMesh QuadTree::getSurrounding(int x, int z, int radius)
{
    QuadMesh m1, m2;

    for (int i = -radius; i <= radius; i++)
    {
        for (int j = -radius; j <= radius; j++)
        {
            float leaf_x = x + (int)Chunk::SIDE * i;
            float leaf_z = z + (int)Chunk::SIDE * j;

            Leaf *leaf = leafAt(leaf_x, leaf_z);
            if (leaf)
            {
                auto meshes = leaf->getMeshes();
                m1 += meshes.first;
                m2 += meshes.second;
            }
        }
    }
    
    m1 += m2;
    return m1;
}

int QuadTree::chunkIDAt(int x, int z)
{
    Leaf *leaf = leafAt(x, z);

    if (leaf)
    {
        return (leaf->chunk).id;
    }

    return -1;
}

#pragma endregion QuadTree