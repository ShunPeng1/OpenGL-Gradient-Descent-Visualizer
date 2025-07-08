#include "Engine/Scenes/Node.h"

Node::Node() : mIsAlive(true), mIsStarted(false), mScenePtr(nullptr), mParent(nullptr)
{

}

Node::~Node()
{

}

void Node::init()
{

}

void Node::tryInit()
{
	if (!mIsAlive) {
		return;
	}

	init();
	for (auto& child : mChildren)
	{
		child->tryInit();
	}
}

void Node::tryStart(IScene* scene)
{
    if (!mIsAlive) {
        return;
    }

	if (!mIsStarted) {
		start(scene);
		mIsStarted = true;
	}

	for (auto& child : mChildren)
	{
		child->tryStart(scene);
	}
}

void Node::tryUpdate(float deltaTime)
{
	if (!mIsAlive){
        return;
	}		

    update(deltaTime);

	for (auto& child : mChildren)
	{
		child->tryUpdate(deltaTime);
	}
}

void Node::tryRender(ShaderProgram& shaderProgram)
{
	if (!mIsAlive){ 
		return;
	}

    render(shaderProgram);

	for (auto& child : mChildren)
	{
		child->tryRender(shaderProgram);
	}
}

void Node::clear()
{
	for (auto& child : mChildren)
	{
		child->clear();
	}

	mChildren.clear();

}

void Node::kill()
{
    if (mIsAlive) {
        mIsAlive = false;
        emit isAliveChanged(mIsAlive);
    }
}

void Node::revive()
{
    if (!mIsAlive) {
        mIsAlive = true;
        emit isAliveChanged(mIsAlive);
    }
}

bool Node::getIsAlive() const
{
	return mIsAlive;
}

void Node::setScene(IScene* scene) {
    mScenePtr = scene;
}

IScene* Node::getScene() const {
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

std::vector<Node*> Node::getChildren() const
{
	std::vector<Node*> children;
	for (const auto& child : mChildren)
	{
		children.push_back(child.get());
	}

	return children;
}

void Node::write(QJsonObject& json) const {
	json[SERIALIZE_NODE_NAME] = objectName();
    json[SERIALIZE_NODE_IS_ALIVE] = mIsAlive;

    QJsonArray childrenArray;
    for (const auto& child : mChildren) {
        QJsonObject childObject;
        child->write(childObject);
        childrenArray.append(childObject);
    }
    json[SERIALIZE_NODE_CHILDREN] = childrenArray;
}

void Node::read(const QJsonObject& json) {
    setObjectName(json[SERIALIZE_NODE_NAME].toString());
    mIsAlive = json[SERIALIZE_NODE_IS_ALIVE].toBool();

    QJsonArray childrenArray = json[SERIALIZE_NODE_CHILDREN].toArray();
    for (int i = 0; i < childrenArray.size(); ++i) {
        QJsonObject childObject = childrenArray[i].toObject();
        std::unique_ptr<Node> child = std::make_unique<Node>();
        child->read(childObject);
        addChild(std::move(child));
    }
}

void* Node::accept(INodeVisitor* visitor)
{
	return visitor->visitNode(this);
}

void Node::start(IScene* scene)
{
	mScenePtr = scene;
}

void Node::update(float deltaTime)
{

}

void Node::render(ShaderProgram& shaderProgram)
{

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
