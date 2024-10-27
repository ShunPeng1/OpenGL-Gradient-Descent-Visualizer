#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Engine/Engine.h"
#include "Engine/Renders/ShaderProgram.h"

class Node
{
public:
	Node();
	virtual ~Node();

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