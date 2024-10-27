#ifndef SCENE_H
#define SCENE_H

#include "Engine/Renders/Mesh.h"
#include "Qt/Inputs/InputPublisher.h"


#include "Engine/Scenes/Node.h"

#include "Engine/Nodes/Camera.h"

#include <vector>
#include <memory>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void load() = 0;
	virtual void init();

	virtual void update(float deltaTime);
	virtual void render();

	int addMesh(std::shared_ptr<Mesh> mesh);
	void addToUpdateList(std::shared_ptr<Node> nodes);
	void addToRenderList(std::shared_ptr<Node> nodes);

	void removeMesh(std::shared_ptr<Mesh> mesh);
	void removeFromUpdateList(std::shared_ptr<Node> nodes);
	void removeFromRenderList(std::shared_ptr<Node> nodes);

	std::shared_ptr<Mesh> getMesh(int index) const;


protected:
	std::shared_ptr<ShaderProgram> mDefaultShader;
	std::vector<std::shared_ptr<Mesh>> mMeshes;
	std::vector<std::shared_ptr<Node>> mUpdateLists;
	std::vector<std::shared_ptr<Node>> mRenderLists;

public: 
	InputPublisher* inputPublisher;
	Camera* camera;


};

#endif // SCENE_H