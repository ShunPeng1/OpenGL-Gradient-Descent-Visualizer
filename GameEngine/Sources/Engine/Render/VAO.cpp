#include "Engine/Render/VAO.h"

VAO::VAO(const void* data, GLsizeiptr size) {
    initializeOpenGLFunctions();
    glGenVertexArrays(1, &mID);
    glBindVertexArray(mID);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &mID);
}

void VAO::Bind() {
    glBindVertexArray(mID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}