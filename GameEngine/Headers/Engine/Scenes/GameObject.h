#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Engine/Scenes/Scene.h"
#include "Engine/Renders/ShaderProgram.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void init(Scene* scene) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(ShaderProgram& shaderProgram) = 0;

	virtual void kill();
	virtual void revive();
	bool getIsAlive() const;

protected:
	bool mIsAlive;
	Scene* mScenePtr;
};

#endif // GAMEOBJECT_H