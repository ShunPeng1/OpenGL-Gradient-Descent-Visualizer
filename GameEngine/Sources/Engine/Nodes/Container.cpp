#include "Engine/Nodes/Container.h"

Container::Container() : Node(), transform(Transform())
{

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
