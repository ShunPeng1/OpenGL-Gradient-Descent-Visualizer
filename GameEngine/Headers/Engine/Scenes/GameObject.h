#pragma once

#include "Engine/Scenes/Scene.h"

class Scene;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void update(float deltaTime) = 0;

	virtual void kill();
	virtual void revive();
	bool isAlive() const;

private:
	bool m_alive;
	Scene* m_scenePtr;
};