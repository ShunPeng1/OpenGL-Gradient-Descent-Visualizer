#ifndef CONTAINER_H
#define CONTAINER_H


#include "Engine/Scenes/GameObject.h"
#include "Engine/Components/Transform.h"

class Container : public GameObject  
{  
public:  
	Container();  
	virtual ~Container() noexcept; // Add noexcept to match the base class destructor

public:  
	Transform mTransform;
};


#endif // !CONTAINER_H
