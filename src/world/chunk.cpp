#include "world/chunk.hpp"
#include <iostream>

Chunk::Chunk()
{
    cubes = new Cube ***[Chunk::WIDTH];

    for (size_t i = 0; i < Chunk::WIDTH; i++)
    {
        cubes[i] = new Cube **[Chunk::HEIGHT];
        for (size_t j = 0; j < Chunk::HEIGHT; j++)
        {
            cubes[i][j] = new Cube *[Chunk::DEPTH] {};
        }
    }

    std::cout << "Chunk created" << std::endl;
}

Chunk::Chunk(int x0, int y0, int z0) : Chunk()
{
    this->x0 = x0;
    this->y0 = y0;
    this->z0 = z0;
}

Chunk::~Chunk()
{
    for (size_t i = 0; i < Chunk::WIDTH; i++)
    {
        for (size_t j = 0; j < Chunk::HEIGHT; j++)
        {
            delete[] cubes[i][j];
        }
        delete[] cubes[i];
    }
    delete[] cubes;
}

void Chunk::placeAt(int x, int y, int z, Cube *c)
{
    cubes[x][y][z] = c;
}

void Chunk::for_each(std::function<void(int, int, int, Cube *)> f)
{
    for (size_t i = 0; i < Chunk::WIDTH; i++)
    {
        for (size_t j = 0; j < Chunk::HEIGHT; j++)
        {
            for (size_t k = 0; k < Chunk::DEPTH; k++)
            {
                if (cubes[i][j][k])
                {
                    f(x0 + i, y0 + j, z0 + k, cubes[i][j][k]);
                }
            }
        }
    }
}

Shape Chunk::getGeometry()
{
    Shape result;
    for_each([&result](int x, int y, int z, Cube *c) {
        Shape sh = c->getShape();
        sh.translate(x, y, z);
        result += sh;
    });

    return result;
}