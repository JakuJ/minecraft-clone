#include "world/block.hpp"

Block::Block(Block::Type t) : type(t) {}

Shape Block::getShape() const
{
    return Shape::Box(glm::vec3(-0.5), glm::vec3(0.5));
}

std::ostream &operator<<(std::ostream &out, const Block &block)
{
    return out << "Block of type " << block.type;
}