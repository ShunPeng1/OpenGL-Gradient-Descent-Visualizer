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

	virtual void init() = 0;

	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

	virtual void addMesh(Mesh* mesh);
	virtual void addGameObject(GameObject* gameObject);
	virtual void addComponent(Component* component);

	virtual void removeMesh(Mesh* mesh);
	virtual void removeGameObject(GameObject* gameObject);
	virtual void removeComponent(Component* component);


private:
	std::vector<Mesh*> mMeshes;
	std::vector<GameObject*> mGameObjects;
	std::vector<Component*> mComponents;
	
};


#endif // !SCENE_H
