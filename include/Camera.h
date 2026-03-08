#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "InputManager.h"

class InputManager;

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float fov = 45.0f;
    float aspect = 16.0f / 9.0f;
    float near = 0.1f, far = 100.0f;

    float moveSpeed = 10.0f;
    float mouseSens = 0.1f;
    float yaw = 90.0f;
    float pitch = 0.0f;

    Camera();

    void update(InputManager &input, float deltaTime);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    void updateCameraDir();
};