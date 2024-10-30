#include "Engine/Scenes/Node.h"

Node::Node()
{
	mIsAlive = true;
}

Node::~Node()
{

}

void Node::tryInit(Scene* scene)
{
	if (!mIsInitialized)
	{
		init(scene);
		mIsInitialized = true;
	}

	for (auto& child : mChildren)
	{
		child->tryInit(scene);
	}
}

void Node::tryUpdate(float deltaTime)
{
	if (mIsAlive)
	{
		update(deltaTime);
	}

	for (auto& child : mChildren)
	{
		child->tryUpdate(deltaTime);
	}
}

void Node::tryRender(ShaderProgram& shaderProgram)
{
	if (mIsAlive)
	{
		render(shaderProgram);
	}

	for (auto& child : mChildren)
	{
		child->tryRender(shaderProgram);
	}
}

void Node::setName(const QString& name)
{
	mName = name;
}

QString Node::getName() const
{
	return mName;
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

void Node::setScene(Scene* scene) {
    mScenePtr = scene;
}

Scene* Node::getScene() const {
    return mScenePtr;
}

void Node::setParent(Node* parent) {
    if (mParent) {
        mParent->removeChild(this);
    }

    mParent = parent;

    if (mParent) {
        mParent->addChild(std::unique_ptr<Node>(this));
    }
}

Node* Node::getParent() const {
    return mParent;
}

int Node::getChildCount() const {
    return mChildren.size();
}

Node* Node::getChild(int index) const {
    if (index < 0 || index >= static_cast<int>(mChildren.size())) {
        return nullptr;
    }
    return mChildren[index].get();
}

void Node::addChild(std::unique_ptr<Node> child) {
    mChildren.push_back(std::move(child));
}

void Node::removeChild(Node* child) {
    auto it = std::remove_if(mChildren.begin(), mChildren.end(),
        [child](const std::unique_ptr<Node>& ptr) {
            return ptr.get() == child;
        });
    if (it != mChildren.end()) {
        mChildren.erase(it, mChildren.end());
    }
}
