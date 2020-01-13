#include <models/Game.hpp>
#include "models/Player.hpp"
#include "utils/Log.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/fast_trigonometry.hpp"
#include "glm/gtx/vec_swizzle.hpp"

Player::Player(const glm::vec3 &position)
        : currentChunkID(-1), position(position), headPitch(0), headYaw(-90) {}

void Player::move(const glm::vec3 &vector) {
    glm::mat4 transform = glm::rotate(glm::mat4(1), glm::radians(-static_cast<float>(headYaw) - 90),
                                      glm::vec3(0, 1, 0));
    glm::vec3 trans = glm::xyz(transform * glm::vec4(vector, 0.0));

    glm::vec3 nextPosition = position + trans * MOVEMENT_SPEED;

    glm::vec<3, int, glm::qualifier::packed> floored = glm::round(nextPosition);

    // Next potential chunk
    Chunk *chunk = Game::getInstance().world.tree.chunkAt(floored.x, floored.z);
    if (!chunk) {
        return;
    }

    floored -= glm::vec3(chunk->x0, 0, chunk->z0);

    auto direction = glm::vec3(1);
    for (int i = -1; i <= 0; i++) {
        for (int j = -2; j <= 0; j++) {
            for (int k = -1; k <= 0; k++) {
                if (chunk->getAt(floored.x + i, floored.y + j, floored.z + k)) {
                    // TODO: Fix behaviour on chunks edges
                    // TODO: Add sliding along walls
                    return;
                }
            }
        }
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
