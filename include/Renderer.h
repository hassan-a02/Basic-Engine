#pragma once

#include "glad/glad.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "stb_image.h"

#include "Scene.h"
#include "Shader.h"

#include <iostream>
#include <memory>

class Renderer
{
public:
    Renderer();

    void drawScene(const std::vector<RenderItem>& renderItems, const std::vector<RenderItem>& renderItemsLightSources, const Camera& cam, const DirectionalLight dirLight, const std::vector<PointLight*> pointLights);


private:
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> lightSourceShader;

    void setUniforms(const RenderItem &item, const Camera& cam, const DirectionalLight dirLight, const std::vector<PointLight*> pointLights);
};