#include <cmath>
#include "world/chunk.hpp"
#include "FastNoiseSIMD/FastNoiseSIMD.h"
#include "world/block.hpp"

u_int Chunk::NEXT_ID = 0;

Chunk::Chunk(int x0, int z0) : x0(x0), z0(z0), blocks(SIDE * SIDE * HEIGHT), id(Chunk::NEXT_ID++) {
    generate(1337);
}

Chunk::~Chunk() {
    for (Block *b : blocks) {
        delete b;
    }
}

constexpr auto &Chunk::at(int x, int y, int z) {
    return blocks[x + y * SIDE + z * SIDE * HEIGHT];
}

void Chunk::placeAt(int x, int y, int z, Block *block) {
    removeAt(x, y, z);
    at(x, y, z) = block;
}

void Chunk::removeAt(int x, int y, int z) {
    delete at(x, y, z);
    at(x, y, z) = nullptr;
}

Block *Chunk::getAt(int x, int y, int z) {
    if (x < 0 || x >= SIDE || y < 0 || y >= HEIGHT || z < 0 || z >= SIDE) {
        return nullptr;
    }
    return at(x, y, z);
}

void Chunk::generate(int seed) {
    static const int BEDROCK_LEVEL = 5;
    static const int STONE_LEVEL = 40;
    static const int SEA_LEVEL = 64;
    static const int SEA_BOTTOM = 50;
    static const int HILL_PEAKS = 80;

    static const int noise_sd = (HILL_PEAKS - SEA_BOTTOM) / 2;
    static const int noise_mean = (HILL_PEAKS + SEA_BOTTOM) / 2;
    static const float noise_scale = 2.0;

    // Noise-based terrain
    FastNoiseSIMD *myNoise = FastNoiseSIMD::NewFastNoiseSIMD(seed);
    myNoise->SetAxisScales(noise_scale, 1.0, noise_scale);

    float *noiseSet = myNoise->GetSimplexSet(x0, 0, z0, SIDE, 1, SIDE);

    u_int index = 0;
    for (u_int x = 0; x < SIDE; x++) {
        for (u_int z = 0; z < SIDE; z++) {
            // Noise-based variation in terrain height
            int groundLevel = floor(noise_mean + noise_sd * noiseSet[index++]);

            // BEDROCK
            for (int y = 0; y < BEDROCK_LEVEL && y < groundLevel; y++) {
                placeAt(x, y, z, new Block(Block::BEDROCK));
            }

            // STONE
            for (int y = BEDROCK_LEVEL; y < STONE_LEVEL && y < groundLevel; y++) {
                placeAt(x, y, z, new Block(Block::STONE));
            }

            bool sea = groundLevel < SEA_LEVEL;

            // DIRT or SAND
            for (int y = STONE_LEVEL; y < groundLevel; y++) {
                placeAt(x, y, z, new Block(sea ? Block::SAND : Block::DIRT));
            }

            if (sea) {
                // WATER
                for (int y = groundLevel; y < SEA_LEVEL; y++) {
                    placeAt(x, y, z, new Block(Block::WATER));
                }
            } else {
                placeAt(x, groundLevel, z, new Block(Block::GRASS));
            }
        }
    }

    FastNoiseSIMD::FreeNoiseSet(noiseSet);
}


