#include "Engine/Scenes/Node.h"

Node::Node()
{
	mIsAlive = true;
}

Node::~Node()
{

}

void Node::kill()
{
	mIsAlive = false;
}

void Node::revive()
{
	mIsAlive = true;
}

bool Node::getIsAlive() const
{
	return mIsAlive;
}
