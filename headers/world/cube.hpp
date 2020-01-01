#pragma once

#include "shape.hpp"

struct Cube
{
    enum Type
    {
        AIR = 0,
        DIRT
    };

    Type type;

    Cube();
    Cube(Type);

    Shape getShape() const;
};