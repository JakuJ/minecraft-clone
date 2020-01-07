#pragma once

#include "glm/glm.hpp"

class Player
{
    static constexpr const float MOVEMENT_SPEED = 20;

public:
    glm::vec3 position;

    float headPitch;
    float headYaw;

    Player(const glm::vec3 &position);

    // Move player by the displacement vector
    void move(const glm::vec3 &);

    // Get first person camera MVP matrix
    glm::mat4 getFPMatrix() const;
};