#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include <vector>
#include <algorithm>
#include <memory>

#include "Entity.h"
#include "Camera.h"
#include "Lighting.h"
#include "TextureManager.h"

class TextureManager;

struct RenderItem
{
    glm::mat4 modelMatrix;
    unsigned int vao;
    unsigned int indexCount;
    Material mat;
    float distanceToCam;

    //Only for light source render queue
    glm::vec3 lightCol;

    bool operator<(const RenderItem& other) const
    {
        return distanceToCam > other.distanceToCam;
    }
};

class Scene
{
public:
    Scene();

    void update(InputManager& input, float deltaTime);
    std::vector<RenderItem> prepareRender();
    std::vector<RenderItem> prepareRenderLightSources();

    const Camera& getCamera();
    std::vector<Entity*> getEntities();
    DirectionalLight getDirLight();
    std::vector<PointLight*> getPointLights();

    void spawnEntity(MeshType meshType, glm::vec3 position = glm::vec3(0.0f, 0.1f, 0.0f));
    void removeEntity(Entity* entity);

    void spawnPointLight(glm::vec3 position = glm::vec3(0.0f, 0.3f, 0.0f), glm::vec3 diffuse = glm::vec3(0.8f));
    void removePointLight(PointLight* light);


private:
    DirectionalLight dirLight;
    std::vector<std::unique_ptr<PointLight>> pointLights;
    std::vector<std::unique_ptr<Entity>> gameObjects;
    std::unique_ptr<Camera> camera;


    std::unique_ptr<TextureManager> textureManager;
    std::vector<RenderItem> renderQueue;
    std::vector<RenderItem> renderQueueLightSources;

    void createDefaultScene();
    void addGameObject(Entity* newGameObject);
};