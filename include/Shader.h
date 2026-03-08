#pragma once

#include "glad/glad.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Utils.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Shader
{
public:
	unsigned int id;

	Shader(const char* vertPath, const char* fragPath);
	~Shader() { GL_CHECK(glDeleteProgram(id)); }

	void use();
	void unbind();

	void setVec3(const std::string& name, const glm::vec3& vec);
	void setMat4(const std::string& name, const glm::mat4& mat);
	void setInt(const std::string& name, const int& integer);
	void setFloat(const std::string& name, const float& f);

private:
	std::unordered_map<std::string, GLint> uniformCache;

	GLint getLocation(const std::string& name);
};

