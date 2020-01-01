#include "world/chunk.hpp"

Chunk::Chunk()
{
    cubes = new Cube**[Chunk::WIDTH];

    for (int i = 0; i < Chunk::WIDTH; i++)
    {
        cubes[i] = new Cube*[Chunk::HEIGHT];
        for(int j = 0; j < Chunk::HEIGHT; j++)
        {
            cubes[i][j] = new Cube[Chunk::DEPTH];
        }
    }
}