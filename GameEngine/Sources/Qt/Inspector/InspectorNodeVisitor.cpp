#include "Qt/Inspector/InspectorNodeVisitor.h"
#include "Engine/Nodes/Camera.h"
#include "Engine/Nodes/Container.h"
#include "Engine/Nodes/MeshRenderer.h"
#include "Engine/Scenes/Node.h"

#include "Qt/Inspector/NodeWidgets/NodeWidget.h"
#include "Qt/Inspector/NodeWidgets/TransformWidget.h"
#include "Qt/Inspector/NodeWidgets/CameraWidget.h"
#include "Qt/Inspector/NodeWidgets/MeshRendererWidget.h"
#include "Qt/Inspector/NodeWidgets/GradientDescentWidget.h"

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
    NodeWidget* nodeWidget = new NodeWidget(node);
    mStackItems.append(nodeWidget);
    return nullptr;
}

void* InspectorNodeVisitor::visitContainer(Container* node) {
    
    Transform * transform = node->transform;
    TransformWidget* transformWidget = new TransformWidget(transform);

    mStackItems.append(transformWidget);

	visitNode(node);
    return nullptr;
}

void* InspectorNodeVisitor::visitMeshRenderer(MeshRenderer* node) {
    
	MeshRendererWidget* transformWidget = new MeshRendererWidget(node);
	mStackItems.append(transformWidget);

    visitContainer(node);

    return nullptr;
}

void* InspectorNodeVisitor::visitCamera(Camera* node) {

    CameraWidget* transformWidget = new CameraWidget(node);
    mStackItems.append(transformWidget);

	visitContainer(node);

    return nullptr;
}

void* InspectorNodeVisitor::visitGradientDescent(GradientDescent* node)
{
	GradientDescentWidget* transformWidget = new GradientDescentWidget(node);
	mStackItems.append(transformWidget);

	visitMeshRenderer(node);
    return nullptr;
}
