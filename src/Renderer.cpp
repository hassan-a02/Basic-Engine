#include "Renderer.h"

Renderer::Renderer()
{
    shader = std::make_unique<Shader>("shaders/basic.vert", "shaders/basic.frag");
    lightSourceShader = std::make_unique<Shader>("shaders/lightSource.vert", "shaders/lightSource.frag");

    GL_CHECK(glEnable(GL_DEPTH_TEST));
}

void Renderer::drawScene(const std::vector<RenderItem>& renderItems, const std::vector<RenderItem>& renderItemsLightSources, const Camera& cam, const DirectionalLight dirLight, const std::vector<PointLight*> pointLights)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));

    for (const auto &item : renderItems)
    {
        setUniforms(item, cam, dirLight, pointLights);

        shader->use();

        GL_CHECK(glActiveTexture(GL_TEXTURE0));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, item.mat.diffuse));

        GL_CHECK(glActiveTexture(GL_TEXTURE1));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, item.mat.specular));

        GL_CHECK(glBindVertexArray(item.vao));
        GL_CHECK(glDrawElements(GL_TRIANGLES, item.indexCount, GL_UNSIGNED_INT, 0));
        GL_CHECK(glBindVertexArray(0));

        shader->unbind();
    }

    for (const auto &item : renderItemsLightSources)
    {
        lightSourceShader->use();

        lightSourceShader->setMat4("model", item.modelMatrix);
        lightSourceShader->setMat4("view", cam.getViewMatrix());
        lightSourceShader->setMat4("projection", cam.getProjectionMatrix());

        lightSourceShader->setVec3("lightCol", item.lightCol);

        GL_CHECK(glBindVertexArray(item.vao));
        GL_CHECK(glDrawElements(GL_TRIANGLES, item.indexCount, GL_UNSIGNED_INT, 0));
        GL_CHECK(glBindVertexArray(0));

        lightSourceShader->unbind();
    }
}

void Renderer::setUniforms(const RenderItem &item, const Camera& cam, const DirectionalLight dirLight, const std::vector<PointLight*> pointLights)
{
    shader->use();

    shader->setMat4("model", item.modelMatrix);
    shader->setMat4("view", cam.getViewMatrix());
    shader->setMat4("projection", cam.getProjectionMatrix());

    shader->setFloat("material.shininess", item.mat.shininess);

    glm::vec3 vsLightDir = glm::mat3(cam.getViewMatrix()) * dirLight.direction;

    shader->setVec3("dirLight.direction", vsLightDir);
    shader->setVec3("dirLight.ambient", dirLight.ambient);
    shader->setVec3("dirLight.diffuse", dirLight.diffuse);
    shader->setVec3("dirLight.specular", dirLight.specular);

    shader->setInt("numOfPointLights", pointLights.size());


    for (int i = 0; i < pointLights.size(); i++)
    {
        glm::vec3 viewPos = glm::vec3(cam.getViewMatrix() * glm::vec4(pointLights[i]->position, 1.0f));

        std::string base = "pointLights[" + std::to_string(i) + "].";

        shader->use();

        shader->setVec3(base + "position", viewPos);
        shader->setVec3(base + "ambient", pointLights[i]->ambient);
        shader->setVec3(base + "diffuse", pointLights[i]->diffuse);
        shader->setVec3(base + "specular", pointLights[i]->specular);
        shader->setFloat(base + "constant", pointLights[i]->constant);
        shader->setFloat(base + "linear", pointLights[i]->linear);
        shader->setFloat(base + "quadratic", pointLights[i]->quadratic);
    }

    shader->unbind();
}