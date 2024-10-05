#pragma once
#ifndef VBO_H
#define VBO_H

#include <QOpenGLExtraFunctions>

class VBO : protected QOpenGLExtraFunctions {
public:
    VBO(const void* data, GLsizeiptr size);
    ~VBO();

    void Bind();
    void Unbind();

private:
    GLuint ID;
};

#endif // VBO_H