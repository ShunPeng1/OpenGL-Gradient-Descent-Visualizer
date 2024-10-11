#include "Engine/Renders/ShaderProgram.h"
#include <QFile>
#include <QTextStream>


ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) : QOpenGLShaderProgram()
{
    initializeOpenGLFunctions();


    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    try
    {
        // open files
        QFile vShaderFile(vertexPath);
        QFile fShaderFile(fragmentPath);

        if (!vShaderFile.open(QIODevice::ReadOnly | QIODevice::Text) || !fShaderFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw std::runtime_error("Failed to open shader files");
        }

        QTextStream vShaderStream(&vShaderFile);
        QTextStream fShaderStream(&fShaderFile);

        // read file's buffer contents into strings
        vertexCode = vShaderStream.readAll().toStdString();
        fragmentCode = fShaderStream.readAll().toStdString();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders

    if (!addShaderFromSourceCode(QOpenGLShader::Vertex, vertexCode.c_str()))
    {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log().toStdString() << std::endl;
    }
    if (!addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentCode.c_str()))
    {
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log().toStdString() << std::endl;
    }
    if (!link())
    {
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log().toStdString() << std::endl;
    }

}

