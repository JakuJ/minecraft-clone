#include <models/Game.hpp>
#include <GLFW/glfw3.h>
#include "models/Player.hpp"
#include "utils/Log.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/fast_trigonometry.hpp"
#include "glm/gtx/vec_swizzle.hpp"

Player::Player(const glm::vec3 &position)
        : currentChunkID(-1), position(position), headPitch(0), headYaw(-90), vertical_v(0), jumping(true),
          swimming(false), isUnderwater(false) {}

void Player::update() {
    static double lastUpdate = 0;

    const auto currentTime = glfwGetTime();
    const auto deltaTime = currentTime - lastUpdate;

    applyGravity(deltaTime);

    lastUpdate = currentTime;
}

void Player::move(glm::vec3 vector) {
    glm::mat4 transform = glm::rotate(glm::mat4(1), glm::radians(-static_cast<float>(headYaw) - 90),
                                      glm::vec3(0, 1, 0));

    glm::vec3 trans = glm::xyz(transform * glm::vec4(vector, 0.0));

    glm::vec3 direction = trans * (swimming ? SWIMMING_SPEED : MOVEMENT_SPEED);

    glm::vec3 nextPosition = position + direction;

    // Block position of the bottom left corner of the feet
    glm::vec<3, int, glm::qualifier::defaultp> floored = glm::floor(nextPosition - glm::vec3(0.5, 1.6, 0.5));

    // Next potential chunk
    Chunk *chunk = Game::getInstance().world.tree.chunkAt(floored.x, floored.z);
    if (!chunk) {
        return;
    }

    // Block position of the eyes
    glm::vec<3, int, glm::qualifier::defaultp> flooredEyes = glm::floor(nextPosition - glm::vec3(0.5, 0, 0.5));

    floored -= glm::vec3(chunk->x0, 0, chunk->z0);
    flooredEyes -= glm::vec3(chunk->x0, 0, chunk->z0);

    // Collision
    swimming = false;
    bool moving = true;

    isUnderwater = false;
    auto headBlock = chunk->getAt(flooredEyes.x, flooredEyes.y, flooredEyes.z);
    if (headBlock && headBlock->isTransparent()) {
        isUnderwater = true;
    }

    // collision 2x3x2 zone
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 2; j++) {
            for (int k = 0; k <= 1; k++) {
                Block *colliding = chunk->getAt(floored.x + i, floored.y + j, floored.z + k);
                if (colliding) {
                    if (colliding->isSolid()) {
                        // TODO: Fix behaviour on chunks edges
                        // TODO: Add sliding along walls
                        // Collision with ground - exit jump mode
                        if (j == 0) {
                            jumping = false;
                            vertical_v = 0;
                        }
                        moving = false;
                    } else {
                        // detect arms in the water
                        if (j == 1) {
                            swimming = true;
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
