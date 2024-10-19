#ifndef COMPONENT_H
#define COMPONENT_H


#include "Engine/Scenes/GameObject.h"

class Component
{
public:
    Component(GameObject* gameObject);
    virtual ~Component();

    virtual Component* clone() = 0;
protected:
    GameObject* mGameObject;
};

#endif // COMPONENT_H