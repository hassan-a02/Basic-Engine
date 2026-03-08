#pragma once

#include "glad/glad.h"

#include <string>
#include <unordered_map>
#include <iostream>

#include "stb_image.h"
#include "Utils.h"

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    unsigned int loadTexture(const std::string &path);
    unsigned int getTexture(const std::string &path);

    unsigned int getDefaultTexture();
    unsigned int getDefaultSpecTexture();

    bool hasTexture(const std::string &path);

private:
    std::unordered_map<std::string, unsigned int> textureMap;
    unsigned int defaultTexture = 0;
    unsigned int defaultSpecTexture = 0;

    unsigned int loadFromFile(const std::string &path);

    void createDefaultTexture();
    void createDefaultSpecTexture();

};