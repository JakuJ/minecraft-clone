#include <iostream>
#include "glm/glm.hpp"
#include "player/player.hpp"

Player::Player(float x, float y, float z) : camera(x, y, z), chunkID(-1)
{
    std::cout << "Player created" << std::endl;
}