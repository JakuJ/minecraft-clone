#pragma once

#include "glm/glm.hpp"
#include "utils/Event.hpp"

class Player {
    static constexpr float MOVEMENT_SPEED = 10;

    int currentChunkID;

public:
    glm::vec3 position;
    double headPitch, headYaw;
    double gravity;
    bool jumping;

    Event<> chunkChanged;

    explicit Player(const glm::vec3 &position);

    // Move player by the displacement vector
    void move(glm::vec3); // NOLINT

    // Get front vector
    [[nodiscard]] glm::vec3 getFront() const;

    // Get first person camera MVP matrix
    [[nodiscard]] glm::mat4 getFPMatrix() const;

    void applyGravity(double deltaTime);

    void jump();
};
