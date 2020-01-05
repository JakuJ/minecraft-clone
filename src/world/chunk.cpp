#include "world/chunk.hpp"
#include "FastNoiseSIMD/FastNoiseSIMD.h"
#include "utility/timing.hpp"
#include "world/block.hpp"
#include <math.h>

u_int Chunk::NEXT_ID = 0;

Chunk::Chunk(int x0, int z0) : x0(x0), z0(z0), id(Chunk::NEXT_ID++)
{
    // allocate memory
    blocks = new Block ***[Chunk::SIDE];

    for (size_t i = 0; i < Chunk::SIDE; i++)
    {
        blocks[i] = new Block **[Chunk::HEIGHT];
        for (size_t j = 0; j < Chunk::HEIGHT; j++)
        {
            blocks[i][j] = new Block *[Chunk::SIDE] { nullptr };
        }
    }

    // generate chunk
    generate(1337);
}

Chunk::~Chunk()
{
    for (size_t i = 0; i < Chunk::SIDE; i++)
    {
        for (size_t j = 0; j < Chunk::HEIGHT; j++)
        {
            delete[] blocks[i][j];
        }
        delete[] blocks[i];
    }
    delete[] blocks;
}

void Chunk::placeAt(u_int x, u_int y, u_int z, Block *c)
{
    removeAt(x, y, z);
    blocks[x][y][z] = c;
}

void Chunk::removeAt(u_int x, u_int y, u_int z)
{
    delete blocks[x][y][z];
    blocks[x][y][z] = nullptr;
}

void Chunk::for_each(std::function<void(int, int, int, Block *)> f) const
{
    for (u_int i = 0; i < Chunk::SIDE; i++)
    {
        for (u_int j = 0; j < Chunk::HEIGHT; j++)
        {
            for (u_int k = 0; k < Chunk::SIDE; k++)
            {
                if (blocks[i][j][k])
                {
                    f(i, j, k, blocks[i][j][k]);
                }
            }
        }
    }
}

Block *Chunk::getAt(int x, int y, int z) const
{
    if (x < 0 || y < 0 || z < 0 || x >= (int)SIDE || y >= (int)HEIGHT || z >= (int)SIDE)
    {
        return nullptr;
    }
    return blocks[x][y][z];
}

void Chunk::generate(int seed)
{
    static const int BEDROCK_LEVEL = 5;
    static const int STONE_LEVEL = 40;
    static const int SEA_LEVEL = 64;
    static const int SEA_BOTTOM = 50;
    static const int HILL_PEAKS = 80;

    static const int noise_sd = (HILL_PEAKS - SEA_BOTTOM) / 2;
    static const int noise_mean = (HILL_PEAKS + SEA_BOTTOM) / 2;
    static const float noise_scale = 2.0;

    MeanScopedTimer timer("Chunk::generate");

    // Noise-based terrain
    FastNoiseSIMD *myNoise = FastNoiseSIMD::NewFastNoiseSIMD(seed);
    myNoise->SetAxisScales(noise_scale, 1.0, noise_scale);

    float *noiseSet = myNoise->GetSimplexSet(x0, 0, z0, SIDE, 1, SIDE);

    u_int index = 0;
    for (u_int x = 0; x < SIDE; x++)
    {
        for (u_int z = 0; z < SIDE; z++)
        {
            // Noise-based variation in terrain height
            int groundLevel = floorf(noise_mean + noise_sd * noiseSet[index++]);

            // BEDROCK
            for (int y = 0; y < BEDROCK_LEVEL && y < groundLevel; y++)
            {
                placeAt(x, y, z, new Block(Block::BEDROCK));
            }

            // STONE
            for (int y = BEDROCK_LEVEL; y < STONE_LEVEL && y < groundLevel; y++)
            {
                placeAt(x, y, z, new Block(Block::STONE));
            }

            bool sea = groundLevel < SEA_LEVEL;

            // DIRT or SAND
            for (int y = STONE_LEVEL; y < groundLevel; y++)
            {
                placeAt(x, y, z, new Block(sea ? Block::SAND : Block::DIRT));
            }

            if (sea)
            {
                // WATER
                for (int y = groundLevel; y < SEA_LEVEL; y++)
                {
                    placeAt(x, y, z, new Block(Block::WATER));
                }
            }
            else
            {
                placeAt(x, groundLevel, z, new Block(Block::GRASS));
            }
        }
    }

    FastNoiseSIMD::FreeNoiseSet(noiseSet);
}

std::ostream &operator<<(std::ostream &out, const Chunk &chunk)
{
    chunk.for_each([&out](u_int x, u_int y, u_int z, Block *block) {
        out << *block << " at (" << x << ", " << y << ", " << z << ")" << std::endl;
    });
    return out;
}