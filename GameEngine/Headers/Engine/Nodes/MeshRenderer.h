#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <QOpenGLExtraFunctions>
#include <memory>

#include "Engine/Enums/RenderMode.h"
#include "Engine/Nodes/Container.h"
#include "Engine/Renders/Mesh.h"

class MeshRenderer : public Container, public QOpenGLExtraFunctions
{
public:
	MeshRenderer();
	MeshRenderer(std::shared_ptr<Mesh> meshID);

	virtual void init() override;
	virtual ~MeshRenderer() noexcept;

	void setMesh(std::shared_ptr<Mesh> meshID);
	std::shared_ptr<Mesh> getMesh() const;
	void setRenderMode(PolygonMode polygonMode, DrawBufferMode drawBufferMode = DrawBufferMode::FRONT_AND_BACK);

	virtual void start(IScene* scene) override;
	virtual void update(float deltaTime) override;
	virtual void render(ShaderProgram& shaderProgram) override;

public: // Interfaces
	virtual void write(QJsonObject& json) const override;
	virtual void read(const QJsonObject& json) override;
	virtual void* accept(INodeVisitor* visitor) override;

protected:
	std::shared_ptr<Mesh> mMesh;
	PolygonMode mPolygonMode;
	DrawBufferMode mDrawBufferMode;
};

#endif // !MESH_RENDERER_H