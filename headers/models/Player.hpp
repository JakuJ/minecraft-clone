#pragma once

#include "glm/glm.hpp"
#include <iostream>
#include "player/camera.hpp"

class PlayerT
{
public:
    glm::vec3 position;
    Camera* camera;

    PlayerT(float x, float y, float z)
    {
        std::cout << "PlayerT created" << std::endl; 
        position = glm::vec3(x, y, z);
    }
};