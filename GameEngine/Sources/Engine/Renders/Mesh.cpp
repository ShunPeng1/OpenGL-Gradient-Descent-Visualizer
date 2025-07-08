#include "Engine/Renders/Mesh.h"

Mesh::Mesh() : mIsStarted(false), mVAO(0), mVBO(0), mEBO(0), mDrawMode(GL_TRIANGLES) 
{

}

Mesh::Mesh(QString path, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->path = path;
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
	this->mDrawMode = GL_TRIANGLES;
}

Mesh::Mesh(QString path, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, GLenum drawMode)
{
	this->path = path;
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	this->mDrawMode = drawMode;
}

void Mesh::init() 
{
    initializeOpenGLFunctions();
}

void Mesh::tryStart()
{
	if (!mIsStarted && !path.isEmpty())
	{
        mIsStarted = true;
		start();
	}
}

void Mesh::start()
{
    setupMesh();
}

void Mesh::setupMesh() {
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::updateMesh(QString newPath, const std::vector<Vertex>& newVertices, const std::vector<unsigned int>& newIndices)
{
    if (mIsStarted) {
        glDeleteBuffers(1, &mVBO);
        glDeleteBuffers(1, &mEBO);
    }

    // Update vertices and indices
	path = newPath;
    vertices = newVertices;
    indices = newIndices;

    // Re-setup the mesh
    setupMesh();
}

void Mesh::write(QJsonObject& json) const {
    json[SERIALIZE_MESH_PATH] = path;


    QJsonArray texturesArray;
    for (const auto& texture : textures) {
        QJsonObject textureObject;
        //texture.write(textureObject); // Assuming Texture class has a write method
        //texturesArray.append(textureObject);
    }
    json[SERIALIZE_MESH_TEXTURES] = texturesArray;

    json[SERIALIZE_MESH_DRAW_MODE] = static_cast<int>(mDrawMode);
}

void Mesh::read(const QJsonObject& json) {
    path = json[SERIALIZE_MESH_PATH].toString();

    vertices.clear();
    indices.clear();
    textures.clear();



    QJsonArray texturesArray = json[SERIALIZE_MESH_TEXTURES].toArray();
    for (int i = 0; i < texturesArray.size(); ++i) {
        QJsonObject textureObject = texturesArray[i].toObject();
        //Texture texture;
        //texture.read(textureObject); // Assuming Texture class has a read method
        //textures.push_back(texture);
    }

    mDrawMode = static_cast<GLenum>(json[SERIALIZE_MESH_DRAW_MODE].toInt());
}

void Mesh::clear()
{
	if (mIsStarted)
	{
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		glDeleteBuffers(1, &mEBO);
	}

}


void Mesh::draw(ShaderProgram& shader) {
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
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);

    /*GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        qDebug() << "OpenGL Error after glBindVertexArray:" << error;
    }*/

    glActiveTexture(GL_TEXTURE0);

	glDrawElements(mDrawMode, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Delete VAO after drawing
    glDeleteVertexArrays(1, &mVAO);

}
