#include "world/Block.hpp"

const bool Block::transparency_table[] = {false, false, false, false, false, true, true, false};
const bool Block::solidity_table[] = {true, true, true, true, true, true, false, true};

std::pair<arr_t, arr_t> Block::getFace(Block::Face face) {
    switch (face) {
        case UP:
            return std::make_pair<arr_t, arr_t>(
                    {0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1},
                    {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0});
        case DOWN:
            return std::make_pair<arr_t, arr_t>(
                    {0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
                    {0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0});
        case BACK:
            return std::make_pair<arr_t, arr_t>(
                    {1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1},
                    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1});
        case FRONT:
            return std::make_pair<arr_t, arr_t>(
                    {0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
                    {0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1});
        case RIGHT:
            return std::make_pair<arr_t, arr_t>(
                    {1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
                    {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0});
        case LEFT:
            return std::make_pair<arr_t, arr_t>(
                    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1},
                    {-1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0});
        default:
            throw std::invalid_argument("Invalid block face!");
    }
}

Block::Block(Block::Type t) : type(t) {}

std::ostream &operator<<(std::ostream &out, const Block &block) {
    return out << "Block of type " << block.type;
}

bool Block::isTransparent() const {
    return transparency_table[type];
}

bool Block::isSolid() const {
    return solidity_table[type];
}
