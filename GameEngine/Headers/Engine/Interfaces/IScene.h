#ifndef ISCENE_H
#define ISCENE_H

#include "Engine/Renders/Mesh.h"
#include "Qt/Inputs/InputPublisher.h"
#include "Engine/Interfaces/ISerializable.h"
#include "Engine/Scenes/Node.h"
#include "Engine/Nodes/Camera.h"
#include "Engine/Scenes/CameraManager.h"

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

    virtual QString getName() const = 0;
    virtual void setName(const QString& name) = 0;

    virtual int addMesh(Mesh* mesh) = 0;
    virtual void removeMesh(Mesh* mesh) = 0;
    virtual Mesh* getMesh(int index) const = 0;

    virtual void addNode(Node* node) = 0;
    virtual void removeNode(Node* node) = 0;
    virtual std::vector<Node*> getNodes() const = 0;

	virtual CameraManager* getCameraManager() = 0;


	virtual void setInputPublisher(InputPublisher* inputPublisher) = 0;
    virtual InputPublisher* getInputPublisher() const = 0;

};

#endif // ISCENE_H