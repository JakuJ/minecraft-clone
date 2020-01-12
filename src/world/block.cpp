#include "world/block.hpp"
#include <utility>

const bool Block::transparency_table[] = {false, false, false, false, false, true, true, false};

Block::Block(Block::Type t) : type(t) {}

std::pair<std::vector<float>, std::vector<float>> Block::getFace(Block::Face face) const {
    switch (face) {
        case UP:
            return std::make_pair(
                    std::vector<float>{0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1},
                    std::vector<float>{0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0});
        case DOWN:
            return std::make_pair(
                    std::vector<float>{0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
                    std::vector<float>{0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0});
        case BACK:
            return std::make_pair(
                    std::vector<float>{1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1},
                    std::vector<float>{0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1});
        case FRONT:
            return std::make_pair(
                    std::vector<float>{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
                    std::vector<float>{0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1});
        case RIGHT:
            return std::make_pair(
                    std::vector<float>{1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
                    std::vector<float>{1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0});
        case LEFT:
            return std::make_pair(
                    std::vector<float>{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1},
                    std::vector<float>{-1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0});
        default:
            throw std::invalid_argument("Invalid block face!");
    }
}

std::ostream &operator<<(std::ostream &out, const Block &block) {
    return out << "Block of type " << block.type;
}
