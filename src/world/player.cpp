#include "world/player.hpp"
#include <iostream>
#include "glm/glm.hpp"

Player::Player(float x, float y, float z) : camera(x, y, z)
{
    std::cout << "Player created" << std::endl;
}