#pragma once

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
};