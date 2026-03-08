#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include "Scene.h"

enum class InspectorMode
{
    Entity, Light, NoInspector
};

class Menu
{
public:
    Menu(GLFWwindow* window);
    ~Menu();


    void render(const std::unique_ptr<Scene>& scene, double fps);

private:
    int selectedIndex = -1;
    InspectorMode inspectorMode = InspectorMode::NoInspector;

    void buildFPS(double fps);
    InspectorMode buildSceneHierarchy(const std::unique_ptr<Scene>& scene);
    void buildInspector(const std::unique_ptr<Scene>& scene);
    void buildSpawner(const std::unique_ptr<Scene>& scene);
};