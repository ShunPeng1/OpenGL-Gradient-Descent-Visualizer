#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();

    // utility uniform functions
    void setUniformBool(const std::string& name, bool value) const;
    void setUniformInt(const std::string& name, int value) const;
    void setUniformFloat(const std::string& name, float value) const;
	void setUniformVec2(const std::string& name, glm::vec2 value) const;
	void setUniformVec3(const std::string& name, glm::vec3 value) const;
	void setUniformVec4(const std::string& name, glm::vec4 value) const;
	void setUniformMat2(const std::string& name, glm::mat2 value) const;
	void setUniformMat3(const std::string& name, glm::mat3 value) const;
	void setUniformMat4(const std::string& name, glm::mat4 value) const;
private: 
	void checkCompileErrors(unsigned int shader, std::string type); 
};

#endif