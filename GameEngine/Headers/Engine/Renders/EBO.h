#ifndef EBO_H
#define EBO_H

#include <QOpenGLExtraFunctions>

class EBO : protected QOpenGLExtraFunctions {
public:
    EBO(const void* data, GLsizeiptr size);
    ~EBO();

    void bind();
    void unbind();

private:
    GLuint mID;
};

#endif // EBO_H