#pragma once

#include "Engine/Renders/Mesh.h"
#include "Engine/Scenes/GameObject.h"
#include <vector>

class GameObject;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;

private:
	std::vector<Mesh*> m_meshes;
	std::vector<GameObject*> m_gameObjects;
	
};

