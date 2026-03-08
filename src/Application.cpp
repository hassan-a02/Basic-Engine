#include "Application.h"

Application::Application()
{
    window = std::make_unique<Window>(1920, 1280, "Game");
    renderer = std::make_unique<Renderer>();
    scene = std::make_unique<Scene>();
    menu = std::make_unique<Menu>(window->getWindow());

    input.init(window->getWindow());

    deltaTime = 0.0;

    frameCount = 0;
    fps = 0.0;
}

void Application::updateFPS()
{
    frameCount++;

    double currentTime = glfwGetTime();
    double elapsed = currentTime - lastTimeFPS;


    if (elapsed >= 1.0)
    {
        fps = frameCount / elapsed;

        frameCount = 0;
        lastTimeFPS = currentTime;
    }
}

void Application::run()
{
    double lastFrame = 0.0;
    lastTimeFPS = glfwGetTime();

    while (!glfwWindowShouldClose(window->getWindow()))
    {
        window->pollEvents();

        static bool keyWasPressed = false;
        bool keyPressed = input.isKeyPressed(GLFW_KEY_TAB);

        if (keyPressed && !keyWasPressed)
        {
            viewportMode = !viewportMode;

            if (viewportMode)
            {
                glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                input.resetMouseDelta();
            }
                
            else
                glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        keyWasPressed = keyPressed;

        if (viewportMode)
        {
            input.update();

            if (input.isKeyPressed(GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(window->getWindow(), true);
        }

        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (viewportMode)
            scene->update(input, deltaTime);
        renderer->drawScene(scene->prepareRender(), scene->prepareRenderLightSources(), scene->getCamera(), scene->getDirLight(), scene->getPointLights());

        updateFPS();

        menu->render(scene, fps);

        window->swapBuffers();
    }
}