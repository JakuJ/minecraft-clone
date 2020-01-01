#pragma once

#include "buffers/buffers.hpp"
#include "world/cube.hpp"
#include "shape.hpp"
#include <functional>

class Chunk
{
    static const unsigned int WIDTH = 16;
    static const unsigned int DEPTH = 16;
    static const unsigned int HEIGHT = 16;

    int x0, y0, z0;
    Cube ****cubes;

    void for_each(std::function<void(int, int, int, Cube*)>);

public:
    Chunk();
    Chunk(int, int, int);
    ~Chunk();

    void placeAt(int, int, int, Cube*);
    Shape getGeometry();
};