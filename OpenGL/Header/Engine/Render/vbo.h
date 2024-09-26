#pragma once
#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>

class VBO {
public:
    VBO(const void* data, GLsizeiptr size);
    ~VBO();

    void bind() const;
    void unbind() const;

private:
    GLuint ID;
};

#endif // VBO_H