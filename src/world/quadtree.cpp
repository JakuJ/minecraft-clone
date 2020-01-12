#include <cmath>
#include <utils/Log.hpp>
#include "world/quadtree.hpp"

Node::Node(int level) : level(level) {
    int coord = static_cast<int>(getExtent() / 2);
    x0 = -coord;
    z0 = -coord;
}

Node::Node(int level, int x0, int z0) : level(level), x0(x0), z0(z0) {}

double Node::getExtent() const {
    return pow(2, level) * Chunk::SIDE;
}

Branch::Branch(int level) : Node(level) {
    q1 = q2 = q3 = q4 = nullptr;
}

Branch::Branch(int level, int x0, int z0) : Node(level, x0, z0) {
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
    int width = static_cast<int>(getExtent() / 2);
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

Leaf::Leaf(int x0, int z0) : Node(0, x0, z0), chunk(x0, z0) {
}

QuadTree::QuadTree(int depth) : root(depth) {
}

Leaf *QuadTree::leafAt(int x, int z) {
    auto extent = root.getExtent() / 2;

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

Chunk *QuadTree::chunkAt(int x, int z) {
    Leaf *leaf = leafAt(x, z);
    return leaf ? &leaf->chunk : nullptr;
}

ChunkSector QuadTree::getSurrounding(int x, int z, int radius) {
    MeanScopedTimer timer("QuadTree::getSurrounding");

    const int side = (2 * radius + 1);

    std::vector<Chunk *> chunks;
    chunks.reserve(side * side);

    for (int j = -radius; j <= radius; j++) {
        for (int i = -radius; i <= radius; i++) {
            chunks.push_back(&leafAt(x + Chunk::SIDE * i, z + Chunk::SIDE * j)->chunk);
        }
    }

    return ChunkSector(chunks, side);
}
