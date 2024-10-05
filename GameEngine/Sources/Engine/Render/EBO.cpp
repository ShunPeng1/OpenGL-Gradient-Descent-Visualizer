#include "Engine/Render/EBO.h"

EBO::EBO(const void* data, GLsizeiptr size) {
    initializeOpenGLFunctions();
    glGenBuffers(1, &mID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

EBO::~EBO() {
    glDeleteBuffers(1, &mID);
}

void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}