#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"


#include <iostream>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    void swapBuffers();
    void pollEvents();

    int getWidth();
    int getHeight();

    GLFWwindow* getWindow();

private:
    GLFWwindow* window;
    int width;
    int height;
};