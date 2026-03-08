#include "Lighting.h"

PointLight::PointLight()
{
    mesh = std::make_unique<Mesh>();

    mesh->setCube();
}

glm::mat4 PointLight::getModelMatrix()
{
    glm::mat4 model(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.25f));

    return model;
}
