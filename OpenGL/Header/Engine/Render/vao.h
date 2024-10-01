
#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>

class VAO {
public:
    VAO();
    ~VAO();

    void Bind() const;
    void Unbind() const;

private:
    GLuint ID;
};

#endif // VAO_H