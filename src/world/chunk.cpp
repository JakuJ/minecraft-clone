#include "world/chunk.hpp"

Chunk::Chunk()
{
    cubes = new Cube ***[Chunk::SIDE];

    for (size_t i = 0; i < Chunk::SIDE; i++)
    {
        cubes[i] = new Cube **[Chunk::HEIGHT];
        for (size_t j = 0; j < Chunk::HEIGHT; j++)
        {
            cubes[i][j] = new Cube *[Chunk::SIDE] { nullptr };
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
            delete[] cubes[i][j];
        }
        delete[] cubes[i];
    }
    delete[] cubes;
}

void Chunk::placeAt(u_int x, u_int y, u_int z, Cube *c)
{
    cubes[x][y][z] = c;
}

void Chunk::for_each(std::function<void(u_int, u_int, u_int, Cube *)> f) const
{
    for (u_int i = 0; i < Chunk::SIDE; i++)
    {
        for (u_int j = 0; j < Chunk::HEIGHT; j++)
        {
            for (u_int k = 0; k < Chunk::SIDE; k++)
            {
                if (cubes[i][j][k])
                {
                    std::cout << "Accessing cube" << std::endl;
                    f(i, j, k, cubes[i][j][k]);
                }
            }
        }
    }
}

Shape Chunk::getShape() const
{
    std::cout << "Getting shape for:" << std::endl;
    std::cout << *this << std::endl;

    Shape result;
    for_each([&result](u_int x, u_int y, u_int z, Cube *c) {
        Shape sh = c->getShape();
        sh.translate(x, y, z);
        result += sh;
    });

    return result;
}

std::ostream &operator<<(std::ostream &out, const Chunk &chunk)
{
    chunk.for_each([&out](u_int x, u_int y, u_int z, Cube *c) {
        out << *c << std::endl;
    });
    return out;
}