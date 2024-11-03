#ifndef ISCENE_H
#define ISCENE_H

#include "Engine/Renders/Mesh.h"
#include "Qt/Inputs/InputPublisher.h"
#include "Engine/Interfaces/ISerializable.h"
#include "Engine/Scenes/Node.h"
#include "Engine/Nodes/Camera.h"

#include <vector>
#include <memory>
#include <QJsonObject>
#include <QJsonArray>

class IScene
{
public:
    virtual ~IScene() {}
	virtual IScene* clone() const = 0;

    virtual void load() = 0;
    virtual void create() = 0;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
	virtual void clear() = 0;

    virtual int addMesh(std::shared_ptr<Mesh> mesh) = 0;
    virtual void removeMesh(std::shared_ptr<Mesh> mesh) = 0;
    virtual std::shared_ptr<Mesh> getMesh(int index) const = 0;

    virtual void addNode(Node* node) = 0;
    virtual void removeNode(Node* node) = 0;

	virtual void setInputPublisher(InputPublisher* inputPublisher) = 0;
	virtual void setCamera(Camera* camera) = 0;

    virtual InputPublisher* getInputPublisher() const = 0;
    virtual Camera* getCamera() const = 0;
};

#endif // ISCENE_H