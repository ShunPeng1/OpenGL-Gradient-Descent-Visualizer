#include "Engine/Renders/ShaderProgram.h"
#include <QFile>
#include <QTextStream>
#include <iostream>

ShaderProgram::ShaderProgram(QString vertexPath, QString fragmentPath)
    : mIsStarted(false), mProgram(nullptr)
{
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


    mProgram = new QOpenGLShaderProgram();

    if (!mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexCode))
    {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << mProgram->log().toStdString() << std::endl;
    }
    if (!mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentCode))
    {
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << mProgram->log().toStdString() << std::endl;
    }

    // Bind attribute locations before linking
    mProgram->bindAttributeLocation("position", 0);
    mProgram->bindAttributeLocation("normal", 1);
    mProgram->bindAttributeLocation("texCoord", 2);
    mProgram->bindAttributeLocation("color", 3);

    if (!mProgram->link())
    {
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << mProgram->log().toStdString() << std::endl;
    }


    mProgram->bind();
    mProgram->setUniformValue("mColorFactor", 1.0f);
    mProgram->setUniformValue("mTextureFactor", 0.0f);
    mProgram->setUniformValue("mPhongFactor", 0.0f);
    mProgram->setUniformValue("mShininess", 32.0f);
    mProgram->setUniformValue("mLightPosition", QVector3D(0.0f, 0.0f, 10.0f));
    mProgram->setUniformValue("mTexScale", QVector2D(1.0f, 1.0f));
    mProgram->setUniformValue("mWorld", QMatrix4x4());
    mProgram->setUniformValue("mView", QMatrix4x4());
    mProgram->setUniformValue("mProj", QMatrix4x4());
    mProgram->setUniformValue("mMaterial", QMatrix3x3());
    mProgram->setUniformValue("mLightIntensity", QMatrix3x3());

    mProgram->release();
}

void ShaderProgram::clear()
{
    if (mProgram)
    {
        mProgram->release();
        delete mProgram;
        mProgram = nullptr;
    }

    mIsStarted = false;
}

void ShaderProgram::bind()
{
    if (mProgram)
    {
        mProgram->bind();
    }
}

void ShaderProgram::release()
{
    if (mProgram)
    {
        mProgram->release();
    }
}

void ShaderProgram::bindAttributeLocation(const char* name, int location)
{
    if (mProgram)
    {
        mProgram->bindAttributeLocation(name, location);
    }
}

void ShaderProgram::setUniformValue(const char* name, bool value)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, value);
    }
}

void ShaderProgram::setUniformValue(const char* name, int value)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, value);
    }
}

void ShaderProgram::setUniformValue(const char* name, float value)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, value);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QMatrix4x4& value)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, value);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QMatrix3x3& value)
{
	if (mProgram)
	{
		mProgram->setUniformValue(name, value);
	}
}

void ShaderProgram::setUniformValue(const char* name, const QVector2D& value)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, value);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QVector3D& value)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, value);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QVector4D& value)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, value);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QColor& color)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, color);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QPoint& point)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, point);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QPointF& point)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, point);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QSize& size)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, size);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QSizeF& size)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, size);
    }
}

void ShaderProgram::setUniformValue(const char* name, const QTransform& value)
{
    if (mProgram)
    {
        mProgram->setUniformValue(name, value);
    }
}