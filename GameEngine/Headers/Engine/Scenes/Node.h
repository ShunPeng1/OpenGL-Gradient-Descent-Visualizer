#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Engine/Engine.h"
#include "Engine/Renders/ShaderProgram.h"

#include "Engine/Interfaces/ISerializable.h"

class Node : public ISerializable
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

	virtual void write(QJsonObject& json) const;
	virtual void read(const QJsonObject& json);

protected:
	virtual void init(Scene* scene);
	virtual void update(float deltaTime);
	virtual void render(ShaderProgram& shaderProgram);

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