#include <models/Game.hpp>
#include "models/Player.hpp"
#include "utils/Log.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/fast_trigonometry.hpp"
#include "glm/gtx/vec_swizzle.hpp"

Player::Player(const glm::vec3 &position)
        : currentChunkID(-1), position(position), headPitch(0), headYaw(-90), vertical_v(0), jumping(true),
          swimming(false), isUnderwater(false) {}

void Player::move(glm::vec3 vector) {
    glm::mat4 transform = glm::rotate(glm::mat4(1), glm::radians(-static_cast<float>(headYaw) - 90),
                                      glm::vec3(0, 1, 0));
    glm::vec3 trans = glm::xyz(transform * glm::vec4(vector, 0.0));

    glm::vec3 nextPosition = position + trans * (swimming ? SWIMMING_SPEED : MOVEMENT_SPEED);

    glm::vec<3, int, glm::qualifier::packed> floored = glm::round(nextPosition);

    // Next potential chunk
    Chunk *chunk = Game::getInstance().world.tree.chunkAt(floored.x, floored.z);
    if (!chunk) {
        return;
    }

    floored -= glm::vec3(chunk->x0, 0, chunk->z0);

    // Collision
    auto direction = glm::vec3(1);
    swimming = false;
    isUnderwater = false;
    bool moving = true;

    for (int i = -1; i <= 0; i++) {
        for (int j = -2; j <= 0; j++) {
            for (int k = -1; k <= 0; k++) {
                Block *colliding = chunk->getAt(floored.x + i, floored.y + j, floored.z + k);
                if (colliding) {
                    if (colliding->isSolid()) {
                        // TODO: Fix behaviour on chunks edges
                        // TODO: Add sliding along walls
                        // Collision with ground - exit jump mode
                        if (j == -2) {
                            jumping = false;
                            vertical_v = 0;
                        }
                        moving = false;
                    } else {
                        // detect arms in the water
                        if (j == -1) {
                            swimming = true;
                        } else if (j == 0) {  // detect head under water
                            isUnderwater = true;
                        }
                    }
                }
            }
        }
    }

    if (!moving) {
        return;
    }

    // Update position
    position = nextPosition;

    // Check if the player crossed from one chunk to another
    if (currentChunkID != chunk->id) {
        Log::debug("Crossing from chunk ", currentChunkID, " to ", chunk->id);
        chunkChanged.raise();
        currentChunkID = chunk->id;
    }
}

glm::vec3 Player::getFront() const {
    glm::vec3 front;
    front.x = glm::fastCos(glm::radians(headYaw)) * cos(glm::radians(headPitch));
    front.y = glm::fastSin(glm::radians(headPitch));
    front.z = glm::fastSin(glm::radians(headYaw)) * cos(glm::radians(headPitch));

    return glm::normalize(front);
}

glm::mat4 Player::getFPMatrix() const {
    glm::mat4 mvp = glm::infinitePerspective(glm::radians(60.0), 4.0 / 3.0, 0.1);
    mvp *= glm::lookAt(position, position + getFront(), glm::vec3(0, 1, 0));
    return mvp;
}

void Player::applyGravity(double deltaTime) {
    move(glm::vec3(0, deltaTime * vertical_v, 0));
    if (swimming) {
        vertical_v = -SWIMMING_SPEED;  // sinking
    } else {
        vertical_v -= deltaTime * GRAVITY_C;  // apply gravity
    }
}

void Player::jump() {
    if (swimming) {
        vertical_v = SWIMMING_SPEED;
    } else if (!jumping) {
        jumping = true;
        vertical_v = FALL_SPEED;  // 0.5s jumps
    }
}
