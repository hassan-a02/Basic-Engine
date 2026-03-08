#include "Camera.h"

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 5.0f);
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::update(InputManager &input, float deltaTime)
{
    glm::vec3 forward = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(forward, up));

    glm::vec3 movement(0.0f);

    if (input.isKeyPressed(GLFW_KEY_W))
        movement += forward;
    if (input.isKeyPressed(GLFW_KEY_S))
        movement -= forward;
    if (input.isKeyPressed(GLFW_KEY_D))
        movement += right;
    if (input.isKeyPressed(GLFW_KEY_A))
        movement -= right;
    if (input.isKeyPressed(GLFW_KEY_SPACE))
        movement += up;
    if (input.isKeyPressed(GLFW_KEY_LEFT_CONTROL))
        movement -= up;

    position += movement * moveSpeed * deltaTime;



    glm::vec2 mouseDelta = input.getMouseDelta();
    yaw += mouseDelta.x * mouseSens;
    pitch += mouseDelta.y * mouseSens;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    

    updateCameraDir();
}

void Camera::updateCameraDir()
{
    glm::vec3 dir;
    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    target = position + glm::normalize(dir);
}
