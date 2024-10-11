#include "Engine/Scenes/Component.h"

Component::Component(GameObject* gameObject)
{
	m_gameObject = gameObject;
}

Component::~Component()
{

}
