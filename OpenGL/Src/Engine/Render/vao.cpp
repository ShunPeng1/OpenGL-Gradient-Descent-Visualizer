#include "Engine/Render/vao.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &ID);
}

void VAO::Bind() const {
    glBindVertexArray(ID);
}

void VAO::Unbind() const {
    glBindVertexArray(0);
}
