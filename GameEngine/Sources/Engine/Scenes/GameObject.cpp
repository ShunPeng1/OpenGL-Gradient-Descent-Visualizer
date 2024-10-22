#include "Engine/Scenes/GameObject.h"

GameObject::GameObject()
{
	mIsAlive = true;
}

GameObject::~GameObject()
{

}

void GameObject::kill()
{
	mIsAlive = false;
}

void GameObject::revive()
{
	mIsAlive = true;
}

bool GameObject::getIsAlive() const
{
	return mIsAlive;
}
