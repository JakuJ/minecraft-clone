#pragma once

#include "glm/glm.hpp"
#include "utils/Event.hpp"

class Player {
    static constexpr float MOVEMENT_SPEED = 4.3;
    static constexpr float SWIMMING_SPEED = 1.97;
    static constexpr float GRAVITY_C = 9.81;
    static constexpr float FALL_SPEED = 0.25 * GRAVITY_C;

    int currentChunkID;

    double vertical_v;
    bool jumping, swimming;

public:
    /// Eye level position in the game world.
    glm::vec3 position;

    double headPitch, headYaw;

    bool isUnderwater;

    Event<> chunkChanged;

    explicit Player(const glm::vec3 &position);

    /// Update player's state every frame.
    void update();

    /// Move player by the displacement vector
    void move(glm::vec3);

    /// Get front vector
    [[nodiscard]] glm::vec3 getFront() const;

    /// Get first person camera MVP matrix
    [[nodiscard]] glm::mat4 getFPMatrix() const;

    void applyGravity(double deltaTime);

    void jump();
};
