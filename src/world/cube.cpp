#include "world/cube.hpp"

Cube::Cube() : type(Cube::AIR) {}

Cube::Cube(Cube::Type t) : type(t) {}

Shape Cube::getShape() const
{
    return Shape::Box(glm::vec3(-0.5), glm::vec3(0.5));
}

std::ostream &operator<<(std::ostream &out, const Cube &cube)
{
    return out << "Cube of type " << cube.type;
}