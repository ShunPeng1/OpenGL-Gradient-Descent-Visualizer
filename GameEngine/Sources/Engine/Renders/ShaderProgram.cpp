#include "Engine/Renders/ShaderProgram.h"
#include <QFile>
#include <QTextStream>


ShaderProgram::ShaderProgram(QString vertexPath, QString fragmentPath) : QOpenGLShaderProgram()
{
    mIsStarted = false;

    // 1. retrieve the vertex/fragment source code from filePath
    

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
        vertexCode = vShaderStream.readAll();
        fragmentCode = fShaderStream.readAll();

		this->vertexPath = vertexPath;
        this->fragmentPath = fragmentPath;

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }


}

void ShaderProgram::init()
{
    initializeOpenGLFunctions();
}

void ShaderProgram::start()
{

    if (mIsStarted)
        return;

    mIsStarted = true;

    if (!addShaderFromSourceCode(QOpenGLShader::Vertex, vertexCode))
    {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log().toStdString() << std::endl;
    }
    if (!addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentCode))
    {
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log().toStdString() << std::endl;
    }
    if (!link())
    {
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log().toStdString() << std::endl;
    }
}

