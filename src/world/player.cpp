#include "world/player.hpp"
#include <iostream>

Player::Player()
{
    x = y = z = 8;
    pitch = yaw = 0;
    std::cout << "Player created" << std::endl;
}