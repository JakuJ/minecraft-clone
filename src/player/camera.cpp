#include <iostream>
#include "player/camera.hpp"

Camera::Camera(float x, float y, float z, float yaw, float pitch) : yaw(yaw), pitch(pitch), movementSpeed(5), mouseSensitivity(0.2)
{
    position = glm::vec3(x, y, z);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    updateCameraVectors();
    std::cout << "Camera created" << std::endl;
}

glm::mat4 Camera::getViewMatrix() const
{
    glm::mat4 mvp = glm::mat4(1);
    mvp *= glm::perspective<float>(glm::radians(60.0), 800.0 / 600.0, 0.5, 1000);
    mvp *= glm::lookAt(position, position + front, up);
    return mvp;
}

void Camera::processKeyboard(Camera::Movement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;
    switch (direction)
    {
    case FORWARD:
        position += front * velocity;
        break;
    case BACKWARD:
        position -= front * velocity;
        break;
    case LEFT:
        position -= right * velocity;
        break;
    case RIGHT:
        position += right * velocity;
        break;
    case UP:
        position += up * velocity;
        break;
    case DOWN:
        position -= up * velocity;
        break;
    default:
        break;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(newFront);

    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}