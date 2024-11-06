#pragma once

#include "Engine/Engine.h"


class INodeVisitable {
public:
	virtual void* accept(INodeVisitor* visitor) = 0;
};