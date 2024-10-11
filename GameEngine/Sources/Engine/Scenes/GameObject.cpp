#include "Engine/Scenes/GameObject.h"

GameObject::GameObject()
{
	m_alive = true;
}

GameObject::~GameObject()
{

}

void GameObject::kill()
{
	m_alive = false;
}

void GameObject::revive()
{
	m_alive = true;
}

bool GameObject::isAlive() const
{
	return m_alive;
}
