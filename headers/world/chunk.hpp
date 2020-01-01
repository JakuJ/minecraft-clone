#pragma once

#include <iostream>
#include <functional>
#include "world/cube.hpp"
#include "shape.hpp"

class Chunk
{
    static const unsigned int HEIGHT = 8;
    Cube ****cubes;

    void for_each(std::function<void(unsigned int, unsigned int, unsigned int, Cube*)>) const;

public:
    static const unsigned int SIDE = 16;
    
    Chunk();
    ~Chunk();

    void placeAt(unsigned int, unsigned int, unsigned int, Cube*);
    Shape getShape() const;

    friend std::ostream& operator<<(std::ostream&, const Chunk&);
};