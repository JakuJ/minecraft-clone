#include "world/block.hpp"

const bool Block::transparency_table[] = {0, 0, 0, 0, 0, 1, 1, 0};

Block::Block(Block::Type t) : type(t) {}

std::vector<float> Block::getFace(Block::Face face) const
{
    switch (face)
    {
    case UP:
        return std::vector<float>{0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1};
    case DOWN:
        return std::vector<float>{0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0};
    case BACK:
        return std::vector<float>{1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1};
    case FRONT:
        return std::vector<float>{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0};
    case RIGHT:
        return std::vector<float>{1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0};
    case LEFT:
        return std::vector<float>{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1};
    default:
        throw "Invalid block face!";
    }
}

std::ostream &operator<<(std::ostream &out, const Block &block)
{
    return out << "Block of type " << block.type;
}