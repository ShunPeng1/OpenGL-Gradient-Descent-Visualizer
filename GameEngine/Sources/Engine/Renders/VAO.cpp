#include "Engine/Renders/VAO.h"

VAO::VAO(const void* data, GLsizeiptr size) {
    initializeOpenGLFunctions();
    glGenVertexArrays(1, &mID);
    glBindVertexArray(mID);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &mID);
}

void VAO::bind() {
    glBindVertexArray(mID);
}

void VAO::unbind() {
    glBindVertexArray(0);
}