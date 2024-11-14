#pragma once

#include "Engine/Engine.h"


class INodeVisitor {
public:
	virtual void* visit(INodeVisitable* node) = 0;
	virtual void* visitNode(Node* node) = 0;
	virtual void* visitContainer(Container* node) = 0;
	virtual void* visitMeshRenderer(MeshRenderer* node) = 0;
	virtual void* visitCamera(Camera* node) = 0;
	virtual void* visitGradientDescent(GradientDescent* node) = 0;

	virtual ~INodeVisitor() = default;
};