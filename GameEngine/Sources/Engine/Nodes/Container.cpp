#include "Engine/Nodes/Container.h"

Container::Container() : Node(), transform(Transform())
{

    setName("Container");
}

Container::~Container() noexcept
{
}

void Container::setParent(Node* parent)
{
	Node::setParent(parent);

    // Check if the parent is an instance of Container
    Container* parentContainer = dynamic_cast<Container*>(parent);
    if (parentContainer)
    {
        transform.setParent(&parentContainer->transform);
    }
    else
    {
        transform.setParent(nullptr);
    }
}

void Container::write(QJsonObject& json) const
{
}

void Container::read(const QJsonObject& json)
{
}

void* Container::accept(INodeVisitor* visitor)
{
    return visitor->visitContainer(this);
}
