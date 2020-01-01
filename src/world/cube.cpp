#include "world/cube.hpp"

Cube::Cube() : type(Cube::AIR) {}

Cube::Cube(Cube::Type t) : type(t) {}