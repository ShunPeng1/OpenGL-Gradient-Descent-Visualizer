#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm.hpp>

#include "vertex.h"
#include "texture.h"
#include "shader.h"

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(Shader& shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

#endif // MESH_H