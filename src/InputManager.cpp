#include "InputManager.h"

void InputManager::init(GLFWwindow* window)
{
    this->window = window;
    
    glfwGetCursorPos(window, &lastX, &lastY);
}

void InputManager::update()
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);

    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;

        deltaX = 0.0;
        deltaY = 0.0;

        return;
    }


    deltaX = x - lastX;
    deltaY = lastY - y;

    lastX = x;
    lastY = y;
}

void InputManager::resetMouseDelta()
{
    firstMouse = true;
}

bool InputManager::isKeyPressed(int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

glm::vec2 InputManager::getMouseDelta()
{
    return glm::vec2(static_cast<float>(deltaX), static_cast<float>(deltaY));
}
