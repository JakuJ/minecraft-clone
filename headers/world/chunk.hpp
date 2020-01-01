#pragma once

#include "world/cube.hpp"

class Chunk
{
    static const unsigned int WIDTH = 16;
    static const unsigned int DEPTH = 16;
    static const unsigned int HEIGHT = 32;
    Cube ***cubes;

public:
    Chunk();
    ~Chunk();

    void placeAt(int, int, int, Cube);
};