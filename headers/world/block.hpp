#pragma once

#include <iostream>
#include "rendering/shape.hpp"

struct Block
{
    enum Type
    {
        DIRT = 0,
        GRASS
    };

    Type type;

    Block(Type);

    Shape getShape() const;

    friend std::ostream& operator<<(std::ostream&, const Block&);
};