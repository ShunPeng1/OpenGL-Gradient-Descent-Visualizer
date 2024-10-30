#ifndef CONTAINER_H
#define CONTAINER_H


#include "Engine/Scenes/Node.h"
#include "Engine/Nodes/Transform.h"

class Container : public Node  
{  
public:  
	Container();  
	virtual ~Container() noexcept;

	virtual void setParent(Node* parent) override;

public:  
	Transform transform;
};


#endif // !CONTAINER_H
