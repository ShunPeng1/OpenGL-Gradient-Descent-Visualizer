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

	// load -> create -> (init -> update -> render)*
	virtual void load();
	virtual void create();
	void init();
	virtual void update(float deltaTime);
	virtual void render();
	
	virtual IScene* clone() const;

	virtual void write(QJsonObject& json) const;
	virtual void read(const QJsonObject& json);

	int addMesh(std::shared_ptr<Mesh> mesh);
	void removeMesh(std::shared_ptr<Mesh> mesh);
	std::shared_ptr<Mesh> getMesh(int index) const;

	void addNode(Node* node);
	void removeNode(Node* node);


	void setInputPublisher(InputPublisher* inputPublisher);
	InputPublisher* getInputPublisher() const;

	void setCamera(Camera* camera);
	Camera* getCamera() const;

protected:

	std::shared_ptr<ShaderProgram> mDefaultShader;

	std::vector<std::unique_ptr<Node>> mChildrenNodes;
	std::vector<std::shared_ptr<Mesh>> mMeshes;


	InputPublisher* inputPublisher;
	Camera* camera;


};

#endif // SCENE_H