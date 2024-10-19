#ifndef SCENE_H
#define SCENE_H

#include "Engine/Engine.h"

#include "Engine/Renders/Mesh.h"

#include <vector>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void load() = 0;
	virtual void init() = 0;

	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

	void addMesh(Mesh* mesh);
	void addGameObject(GameObject* gameObject);
	void addComponent(Component* component);

	void removeMesh(Mesh* mesh);
	void removeGameObject(GameObject* gameObject);
	void removeComponent(Component* component);


protected:
	std::vector<Mesh*> mMeshes;
	std::vector<GameObject*> mUpdateLists;
	std::vector<GameObject*> mRenderLists;
};


#endif // !SCENE_H
