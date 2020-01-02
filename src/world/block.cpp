#include "world/block.hpp"

Block::Block(Block::Type t) : type(t) {}

std::vector<float> Block::getFace(Block::Face face) const
{
    switch (face)
    {
    case UP:
        return std::vector<float>{0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1};
    case DOWN:
        return std::vector<float>{0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0};
    case NORTH:
        return std::vector<float>{1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1};
    case SOUTH:
        return std::vector<float>{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0};
    case EAST:
        return std::vector<float>{1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0};
    case WEST:
        return std::vector<float>{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1};
    default:
        throw "Invalid block face!";
    }
}

std::ostream &operator<<(std::ostream &out, const Block &block)
{
    return out << "Block of type " << block.type;
}