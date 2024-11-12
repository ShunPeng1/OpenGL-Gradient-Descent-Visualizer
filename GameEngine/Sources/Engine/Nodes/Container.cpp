#include "Engine/Nodes/Container.h"

Container::Container() : Node()
{
    transform = std::make_shared<Transform>(); // Initialize with make_shared
    setObjectName("Container");
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
        transform->setParent(parentContainer->transform.get());
    }
    else
    {
        transform->setParent(nullptr);
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
