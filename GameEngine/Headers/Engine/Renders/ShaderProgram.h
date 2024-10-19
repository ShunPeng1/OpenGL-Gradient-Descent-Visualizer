#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderProgram : public QOpenGLShaderProgram, protected QOpenGLExtraFunctions
{
public:

    // constructor reads and builds the shader
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    
    
};

#endif // SHADER_PROGRAM_H