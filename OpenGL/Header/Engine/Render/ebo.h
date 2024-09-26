#ifndef EBO_H
#define EBO_H

#include <GL/glew.h>

class EBO {
public:
    EBO(const void* data, GLsizeiptr size);
    ~EBO();

    void bind() const;
    void unbind() const;

private:
    GLuint ID;
};

#endif // EBO_H