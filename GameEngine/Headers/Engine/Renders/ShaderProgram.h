#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderProgram : protected QOpenGLExtraFunctions
{
public:
	QString vertexPath;
	QString fragmentPath;

	QString vertexCode;
	QString fragmentCode;

    bool mIsStarted;

    // constructor reads and builds the shader
    ShaderProgram(QString vertexPath, QString fragmentPath);
    void init();
    void start();
    void clear();

    void bind();
	void release();

    void bindAttributeLocation(const char* name, int location);
    void setUniformValue(const char* name, bool value);
    void setUniformValue(const char* name, int value);
    void setUniformValue(const char* name, float value);
    void setUniformValue(const char* name, const QMatrix4x4& value);
	void setUniformValue(const char* name, const QMatrix3x3& value);
    void setUniformValue(const char* name, const QVector2D& value);
    void setUniformValue(const char* name, const QVector3D& value);
    void setUniformValue(const char* name, const QVector4D& value);
    void setUniformValue(const char* name, const QColor& color);
    void setUniformValue(const char* name, const QPoint& point);
    void setUniformValue(const char* name, const QPointF& point);
    void setUniformValue(const char* name, const QSize& size);
    void setUniformValue(const char* name, const QSizeF& size);
    void setUniformValue(const char* name, const QTransform& value);



protected:
	QOpenGLShaderProgram* mProgram;
    
};

#endif // SHADER_PROGRAM_H