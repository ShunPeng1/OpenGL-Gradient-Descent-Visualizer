#ifndef EBO_H
#define EBO_H

#include <GL/glew.h>

class EBO {
public:
    EBO(const void* data, GLsizeiptr size);
    ~EBO();

    void Bind() const;
    void Unbind() const;

private:
    GLuint mID;
};

#endif // EBO_H