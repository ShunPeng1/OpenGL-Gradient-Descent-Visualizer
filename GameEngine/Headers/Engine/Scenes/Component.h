#pragma once

#include "Engine/Scenes/GameObject.h"

class Component
{
public:
	Component(GameObject* gameObject);
	virtual ~Component();

	virtual Component* clone() = 0;
protected:
	GameObject* m_gameObject;
};
