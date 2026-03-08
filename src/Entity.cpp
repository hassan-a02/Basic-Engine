#include "Entity.h"

Entity::Entity(MeshType meshType, glm::vec3 position, const std::string &texturePath, const std::string &specularPath)
{
    this->position = position;
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);

    this->texturePath = texturePath;
    this->specularPath = specularPath;

    mesh = std::make_unique<Mesh>();

    switch (meshType)
    {
    case MeshType::CUBE:
        this->name = "Cube";
        mesh->setCube();
        break;
    case MeshType::PLANE:
        this->name = "Plane";
        mesh->setPlane();
        scaleEntity(glm::vec3(50.0f, 1.0f, 50.0f));
        break;
    }
}

glm::mat4 Entity::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, scale);

    return model;
}

void Entity::scaleEntity(glm::vec3 scale)
{
    this->scale = scale;
}

void Entity::update(float deltaTime)
{
}
