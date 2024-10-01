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
    unsigned int mID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void Use();

    // utility uniform functions
    void SetUniformBool(const std::string& name, bool value) const;
    void SetUniformInt(const std::string& name, int value) const;
    void SetUniformFloat(const std::string& name, float value) const;
	void SetUniformVec2(const std::string& name, glm::vec2 value) const;
	void SetUniformVec3(const std::string& name, glm::vec3 value) const;
	void SetUniformVec4(const std::string& name, glm::vec4 value) const;
	void SetUniformMat2(const std::string& name, glm::mat2 value) const;
	void SetUniformMat3(const std::string& name, glm::mat3 value) const;
	void SetUniformMat4(const std::string& name, glm::mat4 value) const;
private: 
	void CheckCompileErrors(unsigned int shader, std::string type); 
};

#endif