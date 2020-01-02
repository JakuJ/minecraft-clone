#pragma once

#include <iostream>
#include <functional>
#include "world/cube.hpp"
#include "shape.hpp"

class Chunk
{
    static const u_int HEIGHT = 8;
    Cube ****cubes;

    void for_each(std::function<void(u_int, u_int, u_int, Cube *)>) const;

public:
    static const u_int SIDE = 16;

    Chunk();
    ~Chunk();

    void placeAt(u_int, u_int, u_int, Cube *);
    void removeAt(u_int, u_int, u_int);
    Shape getShape() const;

    friend std::ostream &operator<<(std::ostream &, const Chunk &);
};