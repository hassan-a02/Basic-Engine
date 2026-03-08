#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Mesh.h"

class Entity
{
public:
    std::string name;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;


    std::string texturePath;
    std::string specularPath;

    std::unique_ptr<Mesh> mesh;

    Entity(MeshType meshType, glm::vec3 position = glm::vec3(0.0f), const std::string& texturePath = "", const std::string& specularPath = "");


    glm::mat4 getModelMatrix();

    void scaleEntity(glm::vec3 scale);

    void update(float deltaTime);
};