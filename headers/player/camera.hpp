#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include <vector>

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // Euler Angles
    float yaw;
    float pitch;
    // Camera options
    float movementSpeed;
    float mouseSensitivity;

public:
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Movement
    {
        FORWARD = 0,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    glm::vec3 position;

    // Constructor with vectors
    Camera(float x, float y, float z, float yaw = 90, float pitch = 0);

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 getViewMatrix() const;

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(Camera::Movement direction, float deltaTime);

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};