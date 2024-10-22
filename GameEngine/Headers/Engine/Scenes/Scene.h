#ifndef SCENE_H
#define SCENE_H

#include "Engine/Engine.h"

#include "Engine/Renders/Mesh.h"

#include <vector>
#include <memory>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void load() = 0;
	virtual void init() = 0;

	virtual void update(float deltaTime);
	virtual void render();

	int addMesh(std::shared_ptr<Mesh> mesh);
	void addToUpdateList(std::shared_ptr<GameObject> gameObject);
	void addToRenderList(std::shared_ptr<GameObject> gameObject);

	void removeMesh(std::shared_ptr<Mesh> mesh);
	void removeFromUpdateList(std::shared_ptr<GameObject> gameObject);
	void removeFromRenderList(std::shared_ptr<GameObject> gameObject);

	std::shared_ptr<Mesh> getMesh(int index) const;


protected:
	std::shared_ptr<ShaderProgram> mDefaultShader;
	std::vector<std::shared_ptr<Mesh>> mMeshes;
	std::vector<std::shared_ptr<GameObject>> mUpdateLists;
	std::vector<std::shared_ptr<GameObject>> mRenderLists;
};


#endif // !SCENE_H
