
#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>

class VAO {
public:
    VAO();
    ~VAO();

    void bind() const;
    void unbind() const;

private:
    GLuint ID;
};

#endif // VAO_H