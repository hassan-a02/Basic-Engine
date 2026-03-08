#include "Menu.h"

Menu::Menu(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

Menu::~Menu()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();

    ImGui::DestroyContext();
}

void Menu::render(const std::unique_ptr<Scene>& scene, double fps)
{
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    buildFPS(fps);
    inspectorMode = buildSceneHierarchy(scene);

    if (inspectorMode != InspectorMode::NoInspector)
        buildInspector(scene);
    
    buildSpawner(scene);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::buildFPS(double fps)
{
    ImGuiViewport *vp = ImGui::GetMainViewport();

    ImVec2 windowSize = ImVec2(50, 50);
    ImVec2 windowPos = ImVec2(
        vp->WorkPos.x,
        vp->WorkPos.y);

    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("FPS", nullptr, flags);

    ImGui::Text(std::to_string((int)fps).c_str());

    ImGui::End();
}

InspectorMode Menu::buildSceneHierarchy(const std::unique_ptr<Scene>& scene)
{
    ImGuiViewport *vp = ImGui::GetMainViewport();

    ImVec2 windowSize = ImVec2(200, 0);
    ImVec2 windowPos = ImVec2(
        vp->WorkPos.x + 55,
        vp->WorkPos.y);

    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_Once);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    auto entities = scene->getEntities();
    auto lights = scene->getPointLights();

    int total = (int)entities.size() + (int)lights.size();

    std::unordered_map<std::string, int> entityCounts{};

    ImGui::Begin("Scene Objects", nullptr, flags);
    for (int i = 0; i < total; ++i)
    {
        std::string label;
        if (i < (int)entities.size())
        {
            entityCounts[entities[i]->name]++;

            label = entities[i]->name + " " + std::to_string(entityCounts[entities[i]->name]);
        }
        else
            label = "Pointlight " + std::to_string(i - entities.size() + 1);

        if (ImGui::Selectable(label.c_str(), selectedIndex == i))
        {
            if (selectedIndex == i)
            {
                selectedIndex = -1;
                inspectorMode = InspectorMode::NoInspector;
            }
            else
                selectedIndex = i;
            
            
            if (i < (int)entities.size() && selectedIndex != -1)
                inspectorMode = InspectorMode::Entity;
            else if (selectedIndex != -1)
                inspectorMode = InspectorMode::Light;
        }
    }
    ImGui::End();

    return inspectorMode;
}

void Menu::buildInspector(const std::unique_ptr<Scene>& scene)
{
    ImGuiViewport *vp = ImGui::GetMainViewport();

    ImVec2 windowSize = ImVec2(500, 0);
    ImVec2 windowPos = ImVec2(
        vp->WorkPos.x + vp->WorkSize.x - windowSize.x,
        vp->WorkPos.y);

    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
    ImGui::SetNextWindowCollapsed(false, ImGuiCond_Always);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    ImGui::Begin("Inspector");

    if (inspectorMode == InspectorMode::Entity)
    {
        auto entities = scene->getEntities();
        if (selectedIndex >= 0 && selectedIndex < (int)entities.size())
        {
            Entity *e = entities[selectedIndex];
            std::string label = entities[selectedIndex]->name;

            ImGui::Text(label.c_str());
            
            ImGui::DragFloat3("- Position", &e->position.x, 0.05f);
            ImGui::DragFloat3("- Rotation", &e->rotation.x, 0.05f);
            ImGui::DragFloat3("- Scale", &e->scale.x, 0.05f);

            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();

            if (ImGui::Button("Delete"))
            {
                scene->removeEntity(e);

                inspectorMode = InspectorMode::NoInspector;
            }
        }
    }
    else if (inspectorMode == InspectorMode::Light)
    {
        auto entities = scene->getEntities();
        auto lights = scene->getPointLights();

        int lightIndex = selectedIndex - (int)entities.size();

        if (lightIndex >= 0 && lightIndex < (int)lights.size())
        {
            PointLight *l = lights[lightIndex];
            ImGui::Text("Pointlight %d", lightIndex + 1);
            
            ImGui::DragFloat3("- Position", &l->position.x, 0.05f);
            ImGui::ColorPicker3("Colour", &l->diffuse.x, 0.05);

            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();

            if (ImGui::Button("Delete"))
            {
                scene->removePointLight(l);
                inspectorMode = InspectorMode::NoInspector;
            }
                
        }
    }

    ImGui::End();
}

void Menu::buildSpawner(const std::unique_ptr<Scene>& scene)
{
    ImGuiViewport* vp = ImGui::GetMainViewport();

    ImVec2 windowSize = ImVec2(200, 0);
    ImVec2 windowPos = ImVec2(
        vp->WorkPos.x + 260,
        vp->WorkPos.y
    );

    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_Once);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;


    ImGui::Begin("Spawner", nullptr, flags);

    if (ImGui::Button("Cube"))
        scene->spawnEntity(MeshType::CUBE, glm::vec3(0.0f, 0.5f, 0.0f));

    if (ImGui::Button("Light"))
        scene->spawnPointLight(glm::vec3(0.0f, 3.0f, 0.0f));

    ImGui::End();
}
