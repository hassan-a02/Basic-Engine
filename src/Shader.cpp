// src/Shader.cpp

#include "Shader.h"

Shader::Shader(const char* vertPath, const char* fragPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


    try
    {
        
        vShaderFile.open(vertPath);
        fShaderFile.open(fragPath);
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
       
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "couldn't read file: " << e.what() << std::endl;
    }


    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];


    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "vertex shader compilation failed\n" << infoLog << std::endl;
    }


    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "fragment shader compilation failed\n" << infoLog << std::endl;
    }


    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "shader linking failed\n" << infoLog << std::endl;
    }


    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec)
{
    GLint location = getLocation(name);

    glUniform3fv(location, 1, glm::value_ptr(vec));
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
    GLint location = getLocation(name);

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setInt(const std::string& name, const int& integer)
{
    GLint location = getLocation(name);

	glUniform1i(location, integer);
}

void Shader::setFloat(const std::string& name, const float& f)
{
    GLint location = getLocation(name);

	glUniform1f(location, f);
}

GLint Shader::getLocation(const std::string& name)
{
    auto it = uniformCache.find(name);
    if (it != uniformCache.end())
    {
        return it->second;
    }

    GLint location = glGetUniformLocation(id, name.c_str());
    uniformCache[name] = location;
    return location;
}
