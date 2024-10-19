#include "Engine/Scenes/GameObject.h"

GameObject::GameObject()
{
	mAlive = true;
}

GameObject::~GameObject()
{

}

void GameObject::kill()
{
	mAlive = false;
}

void GameObject::revive()
{
	mAlive = true;
}

bool GameObject::isAlive() const
{
	return mAlive;
}
