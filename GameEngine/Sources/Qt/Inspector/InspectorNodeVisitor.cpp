#include "Qt/Inspector/InspectorNodeVisitor.h"
#include "Engine/Nodes/Camera.h"
#include "Engine/Nodes/Container.h"
#include "Engine/Nodes/MeshRenderer.h"
#include "Engine/Scenes/Node.h"

#include "Qt/Inspector/NodeWidgets/TransformWidget.h"

#include "QVBoxLayout"

#include <QLabel>

InspectorNodeVisitor::InspectorNodeVisitor() {
	mStackItems = QList<QWidget*>();

}
InspectorNodeVisitor::~InspectorNodeVisitor() {
	for (QWidget* obj : mStackItems) {
		delete obj;
	}

}

const QList<QWidget*>& InspectorNodeVisitor::getStackItems() const
{
	return mStackItems;
}

void InspectorNodeVisitor::clearStackItems()
{
	mStackItems.clear();
}

void* InspectorNodeVisitor::visit(INodeVisitable* node) {
    return node->accept(this);
}

void* InspectorNodeVisitor::visitNode(Node* node) {
    QLabel* label = new QLabel("Node: " + node->getName());
    mStackItems.append(label);
    return nullptr;
}

void* InspectorNodeVisitor::visitContainer(Container* node) {
    
    // Create and add the TransformWidget
    Transform& transform = node->transform;
    TransformWidget* transformWidget = new TransformWidget();
    transformWidget->setTransform(transform.getWorldPosition(), transform.getWorldRotation(), transform.getWorldScale());
    
    mStackItems.append(transformWidget);

	visitNode(node);
    return nullptr;
}

void* InspectorNodeVisitor::visitMeshRenderer(MeshRenderer* node) {
    
    visitContainer(node);

    return nullptr;
}

void* InspectorNodeVisitor::visitCamera(Camera* node) {
	visitContainer(node);

    return nullptr;
}