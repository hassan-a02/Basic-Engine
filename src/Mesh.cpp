#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    mat.shininess = 32.0f;
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Mesh::setCube()
{
    vertices.clear();

    Vertex verts[24];

    // front
    verts[0].position = glm::vec3(0.5f, 0.5f, 0.0f);
    verts[0].texCoord = glm::vec2(1.0f, 1.0f);
    verts[0].normal = glm::vec3(0.0f, 0.0f, 1.0f);

    verts[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
    verts[1].texCoord = glm::vec2(1.0f, 0.0f);
    verts[1].normal = glm::vec3(0.0f, 0.0f, 1.0f);

    verts[2].position = glm::vec3(-0.5f, 0.5f, 0.0f);
    verts[2].texCoord = glm::vec2(0.0f, 1.0f);
    verts[2].normal = glm::vec3(0.0f, 0.0f, 1.0f);

    verts[3].position = glm::vec3(-0.5f, -0.5f, 0.0f);
    verts[3].texCoord = glm::vec2(0.0f, 0.0f);
    verts[3].normal = glm::vec3(0.0f, 0.0f, 1.0f);

    // back
    verts[4].position = glm::vec3(0.5f, 0.5f, -1.0f);
    verts[4].texCoord = glm::vec2(0.0f, 1.0f);
    verts[4].normal = glm::vec3(0.0f, 0.0f, -1.0f);

    verts[5].position = glm::vec3(0.5f, -0.5f, -1.0f);
    verts[5].texCoord = glm::vec2(0.0f, 0.0f);
    verts[5].normal = glm::vec3(0.0f, 0.0f, -1.0f);

    verts[6].position = glm::vec3(-0.5f, 0.5f, -1.0f);
    verts[6].texCoord = glm::vec2(1.0f, 1.0f);
    verts[6].normal = glm::vec3(0.0f, 0.0f, -1.0f);

    verts[7].position = glm::vec3(-0.5f, -0.5f, -1.0f);
    verts[7].texCoord = glm::vec2(1.0f, 0.0f);
    verts[7].normal = glm::vec3(0.0f, 0.0f, -1.0f);

    // right
    verts[8].position = glm::vec3(0.5f, 0.5f, -1.0f);
    verts[8].texCoord = glm::vec2(0.0f, 1.0f);
    verts[8].normal = glm::vec3(1.0f, 0.0f, 0.0f);

    verts[9].position = glm::vec3(0.5f, -0.5f, -1.0f);
    verts[9].texCoord = glm::vec2(0.0f, 0.0f);
    verts[9].normal = glm::vec3(1.0f, 0.0f, 0.0f);

    verts[10].position = glm::vec3(0.5f, 0.5f, 0.0f);
    verts[10].texCoord = glm::vec2(1.0f, 1.0f);
    verts[10].normal = glm::vec3(1.0f, 0.0f, 0.0f);

    verts[11].position = glm::vec3(0.5f, -0.5f, 0.0f);
    verts[11].texCoord = glm::vec2(1.0f, 0.0f);
    verts[11].normal = glm::vec3(1.0f, 0.0f, 0.0f);

    // left
    verts[12].position = glm::vec3(-0.5f, 0.5f, 0.0f);
    verts[12].texCoord = glm::vec2(0.0f, 1.0f);
    verts[12].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

    verts[13].position = glm::vec3(-0.5f, -0.5f, 0.0f);
    verts[13].texCoord = glm::vec2(0.0f, 0.0f);
    verts[13].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

    verts[14].position = glm::vec3(-0.5f, 0.5f, -1.0f);
    verts[14].texCoord = glm::vec2(1.0f, 1.0f);
    verts[14].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

    verts[15].position = glm::vec3(-0.5f, -0.5f, -1.0f);
    verts[15].texCoord = glm::vec2(1.0f, 0.0f);
    verts[15].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

    // top
    verts[16].position = glm::vec3(0.5f, 0.5f, -1.0f);
    verts[16].texCoord = glm::vec2(1.0f, 1.0f);
    verts[16].normal = glm::vec3(0.0f, 1.0f, 0.0f);

    verts[17].position = glm::vec3(0.5f, 0.5f, 0.0f);
    verts[17].texCoord = glm::vec2(1.0f, 0.0f);
    verts[17].normal = glm::vec3(0.0f, 1.0f, 0.0f);

    verts[18].position = glm::vec3(-0.5f, 0.5f, -1.0f);
    verts[18].texCoord = glm::vec2(0.0f, 1.0f);
    verts[18].normal = glm::vec3(0.0f, 1.0f, 0.0f);

    verts[19].position = glm::vec3(-0.5f, 0.5f, 0.0f);
    verts[19].texCoord = glm::vec2(0.0f, 0.0f);
    verts[19].normal = glm::vec3(0.0f, 1.0f, 0.0f);

    // bottom
    verts[20].position = glm::vec3(0.5f, -0.5f, -1.0f);
    verts[20].texCoord = glm::vec2(1.0f, 0.0f);
    verts[20].normal = glm::vec3(0.0f, -1.0f, 0.0f);

    verts[21].position = glm::vec3(0.5f, -0.5f, 0.0f);
    verts[21].texCoord = glm::vec2(1.0f, 1.0f);
    verts[21].normal = glm::vec3(0.0f, -1.0f, 0.0f);

    verts[22].position = glm::vec3(-0.5f, -0.5f, -1.0f);
    verts[22].texCoord = glm::vec2(0.0f, 0.0f);
    verts[22].normal = glm::vec3(0.0f, -1.0f, 0.0f);

    verts[23].position = glm::vec3(-0.5f, -0.5f, 0.0f);
    verts[23].texCoord = glm::vec2(0.0f, 1.0f);
    verts[23].normal = glm::vec3(0.0f, -1.0f, 0.0f);

    for (int i = 0; i < 24; i++)
    {
        vertices.push_back(verts[i]);
    }

    indices = {
        0, 1, 2,
        1, 3, 2,

        4, 5, 6,
        5, 7, 6,

        8, 9, 10,
        9, 11, 10,

        12, 13, 14,
        13, 15, 14,

        16, 17, 18,
        17, 19, 18,

        20, 21, 22,
        21, 23, 22};

    indexCount = indices.size();

    uploadMesh();
}

void Mesh::setPlane()
{
    vertices.clear();
    indices.clear();

    float minX = -0.5f, maxX = 0.5f;
    float minZ = -1.0f, maxZ = 0.0f;
    float y = -0.5f;

    int subdivisionsX = 10;
    int subdivisionsZ = 10;


    for (int z = 0; z <= subdivisionsZ; z++)
    {
        for (int x = 0; x <= subdivisionsX; x++)
        {
            Vertex vert;

            float xPos = minX + (maxX - minX) * (x / (float)subdivisionsX);
            float zPos = minZ + (maxZ - minZ) * (z / (float)subdivisionsZ);
            vert.position = glm::vec3(xPos, y, zPos);

            vert.texCoord = glm::vec2(
                x / (float)subdivisionsX,
                z / (float)subdivisionsZ);

            vert.normal = glm::vec3(0.0f, 1.0f, 0.0f);

            vertices.push_back(vert);
        }
    }

    for (int z = 0; z < subdivisionsZ; z++)
    {
        for (int x = 0; x < subdivisionsX; x++)
        {
            int topLeft = z * (subdivisionsX + 1) + x;
            int topRight = topLeft + 1;
            int bottomLeft = (z + 1) * (subdivisionsX + 1) + x;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    indexCount = indices.size();
    uploadMesh();
}

void Mesh::uploadMesh()
{
    GL_CHECK(glBindVertexArray(vao));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(glm::vec3))));
    GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(glm::vec3) * 2)));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glEnableVertexAttribArray(2));

    GL_CHECK(glBindVertexArray(0));
}

void Mesh::calculateNormals()
{
    for (auto &vert : vertices)
    {
        vert.normal = glm::vec3(0.0f);
    }

    for (int i = 0; i < indices.size(); i += 3)
    {
        unsigned int i0 = indices[i];
        unsigned int i1 = indices[i + 1];
        unsigned int i2 = indices[i + 2];

        glm::vec3 p0 = vertices[i0].position;
        glm::vec3 p1 = vertices[i1].position;
        glm::vec3 p2 = vertices[i2].position;

        glm::vec3 edge1 = p1 - p0;
        glm::vec3 edge2 = p2 - p0;

        glm::vec3 faceNormal = glm::normalize(glm::cross(edge1, edge2));

        vertices[i0].normal += faceNormal;
        vertices[i1].normal += faceNormal;
        vertices[i2].normal += faceNormal;
    }

    for (auto &vert : vertices)
    {
        vert.normal = glm::normalize(vert.normal);
    }
}

unsigned int Mesh::getVAO()
{
    return vao;
}

unsigned int Mesh::getIndexCount()
{
    return indexCount;
}

Material Mesh::getMaterial()
{
    return mat;
}

void Mesh::setTexture(unsigned int textureID, unsigned int specularID)
{
    mat.diffuse = textureID;

    if (specularID)
        mat.specular = specularID;
}
