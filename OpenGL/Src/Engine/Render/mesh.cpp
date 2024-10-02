#include "Engine/Render/Mesh.h"

Mesh::
Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
	this->mDrawMode = GL_TRIANGLES;

	if (vertices.size() > 0)
		setupMesh();

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, GLenum drawMode)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->mDrawMode = drawMode;

	if (vertices.size() > 0)
		setupMesh();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	// vertex color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader) {
	/*unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader.setUniformInt((name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}*/

	glBindVertexArray(mVAO);
	glDrawElements(mDrawMode, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

