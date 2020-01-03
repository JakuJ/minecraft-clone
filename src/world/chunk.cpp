#include "world/chunk.hpp"
#include "world/block.hpp"
#include <random>

u_int Chunk::NEXT_ID = 0;

Chunk::Chunk() : id(Chunk::NEXT_ID++)
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
    generate(0);

    std::cout << "Chunk " << id << " created" << std::endl;
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

Mesh Chunk::getMesh(float x_off, float z_off) const
{
    Mesh mesh;

    for_each([&](int x, int y, int z, Block *block) {
        Block *up = getAt(x, y + 1, z);
        Block *down = getAt(x, y - 1, z);
        Block *north = getAt(x, y, z + 1);
        Block *south = getAt(x, y, z - 1);
        Block *east = getAt(x + 1, y, z);
        Block *west = getAt(x - 1, y, z);

        Block *faces[]{up, down, north, south, east, west};

        // Only render visible faces
        for (u_int i = 0; i < Block::FACES; i++)
        {
            if (!faces[i])
            {
                Block::Face face = (Block::Face)i;

                std::vector<float> vecs = block->getFace(face);
                for (u_int j = 0; j <= 9; j += 3)
                {
                    vecs[j] += x + x_off;
                    vecs[j + 1] += y;
                    vecs[j + 2] += z + z_off;
                }

                mesh.addQuad(vecs, block->type, face);
            }
        }
    });

    return mesh;
}

void Chunk::generate(int seed)
{
    std::mt19937 gen(seed); //Standard seeded mersenne_twister_engine 
    std::uniform_int_distribution<> dis(-1, 1);

    for(u_int x = 0; x < SIDE; x++)
    {
        for(u_int z = 0; z < SIDE; z++)
        {
            int height = 128 + dis(gen);
            for(int y = 0; y < height; y++)
            {
                placeAt(x, y, z, new Block(Block::STONE));    
            }
            placeAt(x, height, z, new Block(Block::GRASS));
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Chunk &chunk)
{
    chunk.for_each([&out](u_int x, u_int y, u_int z, Block *block) {
        out << *block << " at (" << x << ", " << y << ", " << z << ")" << std::endl;
    });
    return out;
}