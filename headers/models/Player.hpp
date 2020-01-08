#pragma once

#include "glm/glm.hpp"

class Player {
    static constexpr const float MOVEMENT_SPEED = 20;

public:
    glm::vec3 position;

    double headPitch, headYaw;

    explicit Player(const glm::vec3 &position);

    // Move player by the displacement vector
    void move(const glm::vec3 &);

    // Get first person camera MVP matrix
    [[nodiscard]] glm::mat4 getFPMatrix() const;
};
