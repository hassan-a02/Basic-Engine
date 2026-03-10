#pragma once
#include "GLFW/glfw3.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class InputManager
{
public:
    void init(GLFWwindow* window);
    void update();
    void resetMouseDelta();

    bool isKeyPressed(int key);
    glm::vec2 getMouseDelta();

private:
    GLFWwindow *window;
    double lastX = 0.0, lastY = 0.0;
    double deltaX = 0.0, deltaY = 0.0;
    bool firstMouse = true;
};