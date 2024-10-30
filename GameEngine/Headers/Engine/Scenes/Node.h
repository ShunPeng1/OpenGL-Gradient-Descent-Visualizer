#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Engine/Engine.h"
#include "Engine/Renders/ShaderProgram.h"

class Node
{
public:
	Node();
	virtual ~Node();

	virtual void tryInit(Scene* scene) final;
	virtual void tryUpdate(float deltaTime) final;
	virtual void tryRender(ShaderProgram& shaderProgram) final;

	virtual void kill();
	virtual void revive();
	bool getIsAlive() const;

public:
	void setName(const QString& name);
	QString getName() const;
	
	void setScene(Scene* scene);
	Scene* getScene() const;

	virtual void setParent(Node* parent);
	Node* getParent() const;
	
	int getChildCount() const;
	Node* getChild(int index) const;

protected:
	virtual void init(Scene* scene) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(ShaderProgram& shaderProgram) = 0;

	void addChild(std::unique_ptr<Node> child);
	void removeChild(Node* child);

protected:
	bool mIsAlive;
	bool mIsInitialized;
	Scene* mScenePtr;
	QString mName;

	Node* mParent;
	std::vector<std::unique_ptr<Node>> mChildren;
};

#endif // GAMEOBJECT_H