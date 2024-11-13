#ifndef SCENE_H
#define SCENE_H

#include "Engine/Interfaces/IScene.h"
#include "Engine/Interfaces/ISerializable.h"

#include "Engine/Renders/Mesh.h"
#include "Qt/Inputs/InputPublisher.h"


#include "Engine/Scenes/Node.h"
#include "Engine/Nodes/Camera.h"

#include <vector>
#include <memory>


#include <QJsonObject>
#include <QJsonArray>

class Scene : public IScene, public ISerializable
{
public:
	Scene();
	virtual ~Scene();

	// load -> init -> create -> (start -> update -> render)* -> clear
	virtual void load(); // Load from path, such as shaders, textures, meshes, etc.
	virtual void init(); // Initialize initializeOpenGLFunctions() and other OpenGL related stuff
	virtual void create(); 
	virtual void start();
	virtual void update(float deltaTime);
	virtual void render();
	virtual void clear(); // Clear all context of current OpenGL context
	
	virtual IScene* clone() const;

	virtual void write(QJsonObject& json) const;
	virtual void read(const QJsonObject& json);

	QString getName() const;
	void setName(const QString& name);

	int addMesh(Mesh* mesh) override;
	void removeMesh(Mesh* mesh) override;
	Mesh* getMesh(int index) const;

	void addNode(Node* node);
	void removeNode(Node* node);
	virtual std::vector<Node*> getNodes() const;

	std::vector<Camera*> getCameras();
	void setMainCamera(Camera* camera);

	void setInputPublisher(InputPublisher* inputPublisher);
	InputPublisher* getInputPublisher() const;

protected:
	QString mName;

	std::shared_ptr<ShaderProgram> mDefaultShader;

	std::vector<std::unique_ptr<Node>> mChildrenNodes;
	std::vector<Mesh*> mMeshes;
	std::vector<Camera*> mCameras;
	Camera* mMainCamera;

	InputPublisher* inputPublisher;

};

#endif // SCENE_H