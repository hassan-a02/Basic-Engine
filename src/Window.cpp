#include "Window.h"
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* title)
{
    this->width = width;
    this->height = height;
    
    if(!glfwInit())
    {
        std::cerr << "glfw failed to init" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Window creation failed" << std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "OpenGL function loading failed" << std::endl;
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    // Ensure viewport is set to the initial window size and keep it updated
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSwapInterval(0);
}

Window::~Window()
{
    glfwDestroyWindow(window);

    glfwTerminate();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

GLFWwindow *Window::getWindow()
{
    return window;
}
