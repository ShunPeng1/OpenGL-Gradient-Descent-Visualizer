#ifndef NODE_H
#define NODE_H

#include "Engine/Engine.h"
#include "Engine/Interfaces/ISerializable.h"
#include "Engine/Interfaces/INodeVisitable.h"
#include "Engine/Interfaces/INodeVisitor.h"

#include "Engine/Renders/ShaderProgram.h"

#include <vector>
#include <memory>
#include <QObject>

class Node : public QObject, public ISerializable, public INodeVisitable
{
    Q_OBJECT

public:
    Node();
    virtual ~Node();
    
    void tryInit();
    void tryStart(IScene* scene);
    void tryUpdate(float deltaTime);
    void tryRender(ShaderProgram& shaderProgram);
	virtual void clear();

    
    virtual void kill();
    virtual void revive();
    bool getIsAlive() const;

public:
    void setScene(IScene* scene);
    IScene* getScene() const;

    virtual void setParent(Node* parent);
    Node* getParent() const;

    int getChildCount() const;
    Node* getChild(int index) const;
	std::vector<Node*> getChildren() const;
    
public: // Interfaces
    virtual void write(QJsonObject& json) const;
    virtual void read(const QJsonObject& json);
    virtual void* accept(INodeVisitor* visitor);

signals:
    void isAliveChanged(bool isAlive);

protected:
    virtual void init();
    virtual void start(IScene* scene);
    virtual void update(float deltaTime);
    virtual void render(ShaderProgram& shaderProgram);

    void addChild(std::unique_ptr<Node> child);
    void removeChild(Node* child);

protected:
    bool mIsAlive;
    bool mIsStarted;
    IScene* mScenePtr;

    Node* mParent;
    std::vector<std::unique_ptr<Node>> mChildren;
};

#endif // NODE_H