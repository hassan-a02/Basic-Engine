#include "Scene.h"

Scene::Scene()
{
    camera = std::make_unique<Camera>();
    this->textureManager = std::make_unique<TextureManager>();

    createDefaultScene();
}

std::vector<RenderItem> Scene::prepareRender()
{
    renderQueue.clear();

    glm::vec3 camPos = camera->position;

    for (const auto& entity : gameObjects)
    {
        float distance = glm::distance(entity->position, camPos);

        if (distance > 100.0f)
            continue;

        RenderItem renderItem;

        renderItem.modelMatrix = entity->getModelMatrix();
        renderItem.vao = entity->mesh->getVAO();
        renderItem.indexCount = entity->mesh->getIndexCount();
        renderItem.mat = entity->mesh->getMaterial();
        renderItem.distanceToCam = distance;

        renderQueue.push_back(renderItem);
    }

    std::sort(renderQueue.begin(), renderQueue.end());

    return renderQueue;
}

std::vector<RenderItem> Scene::prepareRenderLightSources()
{
    renderQueueLightSources.clear();

    glm::vec3 camPos = camera->position;

    for (const auto& light : pointLights)
    {
        float distance = glm::distance(light->position, camPos);

        if (distance > 100.0f)
            continue;

        RenderItem renderItem;

        renderItem.modelMatrix = light->getModelMatrix();
        renderItem.vao = light->mesh->getVAO();
        renderItem.indexCount = light->mesh->getIndexCount();
        renderItem.mat = light->mesh->getMaterial();
        renderItem.distanceToCam = distance;
        renderItem.lightCol = light->diffuse;

        renderQueueLightSources.push_back(renderItem);
    }

    std::sort(renderQueueLightSources.begin(), renderQueueLightSources.end());

    return renderQueueLightSources;
}

void Scene::update(InputManager &input, float deltaTime)
{
    for (auto &obj : gameObjects)
        obj->update(deltaTime);

    camera->update(input, deltaTime);
}

void Scene::addGameObject(Entity *newGameObject)
{
    if (newGameObject->mesh)
    {
        unsigned int texID;
        unsigned int specularID;

        if (newGameObject->texturePath.empty())
            texID = textureManager->getDefaultTexture();
        else
            texID = textureManager->loadTexture(newGameObject->texturePath);

        if (newGameObject->specularPath.empty())
            specularID = textureManager->getDefaultSpecTexture();
        else
            specularID = textureManager->loadTexture(newGameObject->specularPath);

        newGameObject->mesh->setTexture(texID, specularID);
    }

    std::unique_ptr<Entity> ptr(newGameObject);

    gameObjects.push_back(std::move(ptr));
}

const Camera& Scene::getCamera()
{
    return *camera;
}

std::vector<Entity *> Scene::getEntities()
{
    std::vector<Entity*> entities;

    for (auto& object : gameObjects)
    {
        entities.push_back(object.get());
    }

    return entities;
}

DirectionalLight Scene::getDirLight()
{
    return dirLight;
}

std::vector<PointLight *> Scene::getPointLights()
{
    std::vector<PointLight*> lights;

    for (auto& object : pointLights)
    {
        lights.push_back(object.get());
    }

    return lights;
}

void Scene::spawnEntity(MeshType meshType, glm::vec3 position)
{
    Entity* entity = new Entity(meshType, position);

    addGameObject(entity);
}

void Scene::removeEntity(Entity *entity)
{
    auto it = std::find_if(gameObjects.begin(), gameObjects.end(), 
    [entity](const std::unique_ptr<Entity>& ptr)
    {
        return ptr.get() == entity;
    });

    if (it != gameObjects.end())
        gameObjects.erase(it);
}

void Scene::spawnPointLight(glm::vec3 position, glm::vec3 diffuse)
{
    PointLight* light = new PointLight();

    light->position = position;

    light->ambient = glm::vec3(0.1f);
    light->diffuse = diffuse;
    light->specular = glm::vec3(1.0f);

    light->constant = 1.0f;
    light->linear = 0.09f;
    light->quadratic = 0.032f;

    std::unique_ptr<PointLight> ptr(light);

    pointLights.push_back(std::move(ptr));
}

void Scene::removePointLight(PointLight* light)
{
    auto it = std::find_if(pointLights.begin(), pointLights.end(), 
    [light](std::unique_ptr<PointLight>& ptr)
    {
        return ptr.get() == light;
    });

    if (it != pointLights.end())
        pointLights.erase(it);
}

void Scene::createDefaultScene()
{
    dirLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);

    dirLight.ambient = glm::vec3(0.1f);
    dirLight.diffuse = glm::vec3(0.7f);
    dirLight.specular = glm::vec3(1.0f);

    Entity *plane = new Entity(MeshType::PLANE);
    plane->position = glm::vec3(0.0f, 0.0f, 25.0f);

    addGameObject(plane);
}
