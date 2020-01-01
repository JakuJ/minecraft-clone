#include "world/cube.hpp"

Cube::Cube() : type(Cube::AIR)
{
    std::cout << "Cube created" << std::endl;
}

Cube::Cube(Cube::Type t) : type(t)
{
    std::cout << "Cube created from type" << std::endl;
}

Shape Cube::getShape() const
{
    return Shape::Box(glm::vec3(-0.5), glm::vec3(0.5));
}

std::ostream &operator<<(std::ostream &out, const Cube &cube)
{
    return out << "Cube of type " << cube.type;
}