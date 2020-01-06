#include "models/Player.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/fast_trigonometry.hpp"
#include "glm/gtx/vec_swizzle.hpp"
#include <iostream>

Player::Player(const glm::vec3 &position) : position(position), headPitch(0), headYaw(-90)
{
    std::cout << "Player created" << std::endl;
}

void Player::move(const glm::vec3 &vector)
{
    glm::mat4 transform = glm::rotate(glm::mat4(1), glm::radians(-headYaw - 90), glm::vec3(0, 1, 0));
    glm::vec4 trans = transform * glm::vec4(vector, 0.0);
    position += glm::xyz(trans) * MOVEMENT_SPEED;
}

glm::mat4 Player::getFPMatrix() const
{
    glm::vec3 front;
    front.x = glm::fastCos(glm::radians(headYaw)) * cos(glm::radians(headPitch));
    front.y = glm::fastSin(glm::radians(headPitch));
    front.z = glm::fastSin(glm::radians(headYaw)) * cos(glm::radians(headPitch));

    front = glm::normalize(front);

    glm::mat4 mvp = glm::infinitePerspective(glm::radians(60.0), 8.0 / 6.0, 0.1);
    mvp *= glm::lookAt(position, position + front, glm::vec3(0, 1, 0));
    return mvp;
}
