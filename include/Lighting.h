#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "Mesh.h"

struct DirectionalLight
{
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class PointLight
{
public:
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

    std::unique_ptr<Mesh> mesh;

    PointLight();

    glm::mat4 getModelMatrix();
};