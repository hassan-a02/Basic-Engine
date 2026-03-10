#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "Window.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "Menu.h"

#include <chrono>
#include <memory>

class Application
{
public:
    Application();

    void run();
    void updateFPS();

private:
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Menu> menu;
    InputManager input;

    double deltaTime;
    bool viewportMode = true;

    float frameCount;
    double fps;
    double lastTimeFPS;
};