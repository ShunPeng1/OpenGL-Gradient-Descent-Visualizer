#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm.hpp>

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    virtual void Draw(Shader& shader);
protected:
    //  render data
    unsigned int mVAO, mVBO, mEBO;

    void setupMesh();
};

#endif // MESH_H