#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLExtraFunctions>
#include <glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader : protected QOpenGLExtraFunctions
{
public:
    // the program ID
    unsigned int mID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void Use();

    // utility uniform functions
    void SetUniformBool(const std::string& name, bool value);
    void SetUniformInt(const std::string& name, int value);
    void SetUniformFloat(const std::string& name, float value);
    void SetUniformVec2(const std::string& name, glm::vec2 value);
    void SetUniformVec3(const std::string& name, glm::vec3 value);
    void SetUniformVec4(const std::string& name, glm::vec4 value);
    void SetUniformMat2(const std::string& name, glm::mat2 value);
    void SetUniformMat3(const std::string& name, glm::mat3 value);
    void SetUniformMat4(const std::string& name, glm::mat4 value);

private:
    void CheckCompileErrors(unsigned int shader, std::string type);
};

#endif // SHADER_H