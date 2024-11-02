#ifndef MESH_H
#define MESH_H

#include <vector>
#include <QOpenGLExtraFunctions>

#include "Vertex.h"
#include "Texture.h"
#include "ShaderProgram.h"

#include "Engine/Interfaces/ISerializable.h"

class Mesh : public QOpenGLExtraFunctions, public ISerializable {
public:
    QString path = "";
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    
    Mesh();
    Mesh(QString path, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(QString path, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, GLenum drawMode);
    

    void init();
    void tryStart();
    virtual void write(QJsonObject& json) const;
    virtual void read(const QJsonObject& json);

    virtual void draw(ShaderProgram& shader);


protected:
	virtual void start();

    //  render data
	bool mIsStarted;
    unsigned int mVAO, mVBO, mEBO;
    GLenum mDrawMode; // Member variable to store the drawing mode

    void setupMesh();
};

#endif // MESH_H