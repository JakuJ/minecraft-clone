#include "world/chunk.hpp"

Chunk::Chunk()
{
    blocks = new Block ***[Chunk::SIDE];

    for (size_t i = 0; i < Chunk::SIDE; i++)
    {
        blocks[i] = new Block **[Chunk::HEIGHT];
        for (size_t j = 0; j < Chunk::HEIGHT; j++)
        {
            blocks[i][j] = new Block *[Chunk::SIDE] { nullptr };
        }
    }

    std::cout << "Chunk created" << std::endl;
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

void Chunk::for_each(std::function<void(u_int, u_int, u_int, Block *)> f) const
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

Shape Chunk::getShape() const
{
    Shape result;
    for_each([&result](u_int x, u_int y, u_int z, Block *block) {
        Shape sh = block->getShape();
        sh.translate(x, y, z);
        result += sh;
    });

    return result;
}

std::ostream &operator<<(std::ostream &out, const Chunk &chunk)
{
    chunk.for_each([&out](u_int x, u_int y, u_int z, Block *block) {
        out << *block << " at (" << x << ", " << y << ", " << z << ")" << std::endl;
    });
    return out;
}