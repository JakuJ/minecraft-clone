#include <cmath>
#include "world/quadtree.hpp"

#pragma region Node

Node::Node(unsigned int level) : level(level) {
    int coord = static_cast<int>(getExtent()) / 2;
    x0 = -coord;
    z0 = -coord;
}

Node::Node(unsigned int level, int x0, int z0) : level(level), x0(x0), z0(z0) {}

unsigned int Node::getExtent() const {
    return static_cast<unsigned int>(pow(2, level)) * Chunk::SIDE;
}

#pragma endregion Node
#pragma region Branch

Branch::Branch(unsigned int level) : Node(level) {
    q1 = q2 = q3 = q4 = nullptr;
}

Branch::Branch(unsigned int level, int x0, int z0) : Node(level, x0, z0) {
    q1 = q2 = q3 = q4 = nullptr;
}

Branch::~Branch() {
    delete q1;
    delete q2;
    delete q3;
    delete q4;
}

Node *Branch::makeChild(int x, int z) {
    if (level > 1) {
        return new Branch(level - 1, x, z);
    }
    return new Leaf(x, z);
}

Node *Branch::descent(int x, int z) {
    int width = static_cast<int>(getExtent()) / 2;
    int midX = x0 + width;
    int midZ = z0 + width;

    if (x >= midX && z >= midZ) {
        if (!q1) {
            q1 = makeChild(midX, midZ);
        }
        return q1;
    } else if (x >= midX && z < midZ) {
        if (!q4) {
            q4 = makeChild(midX, z0);
        }
        return q4;
    } else if (x < midX && z >= midZ) {
        if (!q2) {
            q2 = makeChild(x0, midZ);
        }
        return q2;
    } else {
        if (!q3) {
            q3 = makeChild(x0, z0);
        }
        return q3;
    }
}

#pragma endregion Branch

Leaf::Leaf(int x0, int z0) : Node(0, x0, z0), chunk(x0, z0) {
}

#pragma region QuadTree

QuadTree::QuadTree(unsigned int depth) : root(depth) {
}

Leaf *QuadTree::leafAt(int x, int z) {
    int extent = static_cast<int>(root.getExtent()) / 2;

    if (x < -extent || x >= extent || z < -extent || z >= extent) {
        return nullptr;
    }

    Branch *n = &root;
    while (n->level > 1) {
        n = reinterpret_cast<Branch *>(n->descent(x, z));
    }

    return reinterpret_cast<Leaf *>(n->descent(x, z));
}

void QuadTree::insert(int x, int y, int z, Block *block) {
    Leaf *leaf = leafAt(x, z);
    if (leaf) {
        leaf->chunk.placeAt(x - leaf->x0, y, z - leaf->z0, block);
    }
}

void QuadTree::remove(int x, int y, int z) {
    Leaf *leaf = leafAt(x, z);
    if (leaf) {
        leaf->chunk.removeAt(x - leaf->x0, y, z - leaf->z0);
    }
}

int QuadTree::chunkIDAt(int x, int z) {
    Leaf *leaf = leafAt(x, z);

    if (leaf) {
        return leaf->chunk.id;
    }

    return -1;
}

ChunkSector QuadTree::getSurrounding(int x, int z, int radius) {
    MeanScopedTimer timer("QuadTree::getSurrounding");

    const int side = (2 * radius + 1);

    auto ***chunks = new Chunk **[side];

    for (int i = -radius; i <= radius; i++) {
        int cx = i + radius;
        chunks[cx] = new Chunk *[side];

        for (int j = -radius; j <= radius; j++) {
            int cz = j + radius;

            int leaf_x = x + static_cast<int>(Chunk::SIDE) * i;
            int leaf_z = z + static_cast<int>(Chunk::SIDE) * j;

            chunks[cx][cz] = &leafAt(leaf_x, leaf_z)->chunk;
        }
    }

    return ChunkSector(chunks, side);
}

#pragma endregion QuadTree