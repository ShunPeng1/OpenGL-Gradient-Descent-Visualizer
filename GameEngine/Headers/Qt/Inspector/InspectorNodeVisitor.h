#pragma once

#include <QList>
#include <QWidget>
#include "Engine/Interfaces/INodeVisitor.h"

class InspectorNodeVisitor : public INodeVisitor {
public:
	InspectorNodeVisitor();
	~InspectorNodeVisitor();

	const QList<QWidget*>& getStackItems() const;
	void clearStackItems();

	virtual void* visit(INodeVisitable* node) override;
	virtual void* visitNode(Node* node) override;
	virtual void* visitContainer(Container* node) override;
	virtual void* visitMeshRenderer(MeshRenderer* node) override;
	virtual void* visitCamera(Camera* node) override;
	virtual void* visitGradientDescent(GradientDescent* node) override;

private:
	QList<QWidget*> mStackItems;
};