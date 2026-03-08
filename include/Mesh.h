#pragma once

#include "glad/glad.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include <vector>

#include "Material.h"
#include "Utils.h"

enum class MeshType { CUBE, PLANE };

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class Mesh
{
public:
    Mesh();
    ~Mesh();

    unsigned int getVAO();
    unsigned int getIndexCount();
    Material getMaterial();

    void setTexture(unsigned int textureID, unsigned int specularID = 0);

    void setCube();
    void setPlane();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Material mat;

    unsigned int vao, vbo, ebo;
    unsigned int indexCount;

    void uploadMesh();
    void calculateNormals();
};