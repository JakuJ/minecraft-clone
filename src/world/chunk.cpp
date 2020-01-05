#include "world/chunk.hpp"
#include "world/block.hpp"
#include "FastNoiseSIMD/FastNoiseSIMD.h"
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

template <>
std::pair<QuadMesh, QuadMesh> Chunk::getMeshes<QuadMesh>(float x_off, float z_off) const
{
    QuadMesh non_transparent;
    QuadMesh transparent;

    for_each([&](int x, int y, int z, Block *block) {
        Block *up = getAt(x, y + 1, z);
        Block *down = getAt(x, y - 1, z);
        Block *north = getAt(x, y, z + 1);
        Block *south = getAt(x, y, z - 1);
        Block *east = getAt(x + 1, y, z);
        Block *west = getAt(x - 1, y, z);

        Block *faces[]{up, down, north, south, east, west};

        // Only render visible faces
        for (Block::Face face = (Block::Face)0; face < Block::FACES; face++)
        {
            if (!faces[face] || (faces[face]->type != block->type && Block::transparency_table[faces[face]->type]))
            {
                std::vector<float> vecs = block->getFace(face);
                for (int j = 0; j <= 9; j += 3)
                {
                    vecs[j] += x + x_off;
                    vecs[j + 1] += y;
                    vecs[j + 2] += z + z_off;
                }

                if (Block::transparency_table[block->type])
                {
                    transparent.addQuad(vecs, block->type, face);
                }
                else
                {
                    non_transparent.addQuad(vecs, block->type, face);
                }
            }
        }
    });

    return std::make_pair(non_transparent, transparent);
}

template <>
std::pair<InstanceMesh, InstanceMesh> Chunk::getMeshes<InstanceMesh>(float x_off, float z_off) const
{
    InstanceMesh non_transparent;
    InstanceMesh transparent;

    for_each([&](int x, int y, int z, Block *block) {
        // Render complete block if any face is visible

        Block *up = getAt(x, y + 1, z);
        Block *down = getAt(x, y - 1, z);
        Block *north = getAt(x, y, z + 1);
        Block *south = getAt(x, y, z - 1);
        Block *east = getAt(x + 1, y, z);
        Block *west = getAt(x - 1, y, z);

        Block *faces[]{up, down, north, south, east, west};

        bool any = false;
        for (Block *face : faces)
        {
            if (!face || (face->type != block->type && Block::transparency_table[face->type]))
            {
                any = true;
                break;
            }
        }

        if (any)
        {

            if (Block::transparency_table[block->type])
            {
                transparent.addCube(x + x_off, y, z + z_off, block->type);
            }
            else
            {
                non_transparent.addCube(x + x_off, y, z + z_off, block->type);
            }
        }
    });

    return std::make_pair(non_transparent, transparent);
}

std::ostream &operator<<(std::ostream &out, const Chunk &chunk)
{
    chunk.for_each([&out](u_int x, u_int y, u_int z, Block *block) {
        out << *block << " at (" << x << ", " << y << ", " << z << ")" << std::endl;
    });
    return out;
}