#pragma once
#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>

class VBO {
public:
    VBO(const void* data, GLsizeiptr size);
    ~VBO();

    void Bind() const;
    void Unbind() const;

private:
    GLuint ID;
};

#endif // VBO_H