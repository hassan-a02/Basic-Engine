#include "TextureManager.h"

TextureManager::TextureManager()
{
    stbi_set_flip_vertically_on_load(true);
}


TextureManager::~TextureManager()
{
    for (auto& [path, id] : textureMap)
    {
        GL_CHECK(glDeleteTextures(1, &id));
    }

    textureMap.clear();
}


unsigned int TextureManager::loadTexture(const std::string& path)
{
    if (textureMap.find(path) != textureMap.end())
        return textureMap[path];

    unsigned int id = loadFromFile(path);

    if (id != 0)
        textureMap[path] = id;
    
    return id;
}

unsigned int TextureManager::getTexture(const std::string& path)
{
    auto it = textureMap.find(path);

    return (it != textureMap.end()) ? it->second : 0;
}

unsigned int TextureManager::getDefaultSpecTexture()
{
    if (defaultSpecTexture == 0)
        createDefaultSpecTexture();
    
    return defaultSpecTexture;
}

unsigned int TextureManager::getDefaultTexture()
{
    if (defaultTexture == 0)
        createDefaultTexture();
    
    return defaultTexture;
}

bool TextureManager::hasTexture(const std::string& path)
{
    return textureMap.find(path) != textureMap.end();
}


unsigned int TextureManager::loadFromFile(const std::string& path)
{
    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    
    if (!data)
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        std::cerr << "STB Error: " << stbi_failure_reason() << std::endl;
        return 0;
    }

    unsigned int textureID;
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));

    GLenum format = GL_RGB;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
    GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    stbi_image_free(data);
    
    return textureID;
}

void TextureManager::createDefaultTexture()
{
    defaultTexture = loadFromFile("assets/default.png");
}


void TextureManager::createDefaultSpecTexture()
{
    unsigned char whitePixel[] = { 255, 255, 255, 255 };
    
    glGenTextures(1, &defaultSpecTexture);
    glBindTexture(GL_TEXTURE_2D, defaultSpecTexture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}
