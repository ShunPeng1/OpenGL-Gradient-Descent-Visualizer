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
	const QString vertexPath;
	const QString fragmentPath;

	QString vertexCode;
	QString fragmentCode;

    bool mIsStarted;

    // constructor reads and builds the shader
    ShaderProgram(const QString vertexPath, const QString fragmentPath);
    void init();
    void start();

    
};

#endif // SHADER_PROGRAM_H