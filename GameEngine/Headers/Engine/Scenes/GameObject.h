#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Engine/Scenes/Scene.h"

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
	bool mAlive;
	Scene* mScenePtr;
};

#endif // GAMEOBJECT_H