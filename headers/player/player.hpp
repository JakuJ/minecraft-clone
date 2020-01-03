#pragma once

#include "camera.hpp"

class Player
{
public:
    Camera camera;

    int chunkID;

    Player(float, float, float);
};