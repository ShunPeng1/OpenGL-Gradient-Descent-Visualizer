#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <QOpenGLExtraFunctions>
#include <memory>

#include "Engine/Enums/RenderMode.h"
#include "Engine/Nodes/Container.h"
#include "Engine/Renders/Mesh.h"
#include "Engine/Components/Material.h"

class MeshRenderer : public Container, public QOpenGLExtraFunctions
{
	Q_OBJECT
public:
	MeshRenderer();
	MeshRenderer(Mesh* mesh, Material *material = nullptr, bool isInstance = false);

	virtual ~MeshRenderer() noexcept;

	void setMesh(Mesh* mesh, bool isInstance);
	Mesh* getMesh() const;

	void setMaterial(Material* material);
	Material* getMaterial();

	void setPolygonMode(PolygonMode polygonMode);
	void setDrawBufferMode(DrawBufferMode drawBufferMode);
	PolygonMode getPolygonMode() const;
	DrawBufferMode getDrawBufferMode() const;

	virtual void init() override;
	virtual void start(IScene* scene) override;
	virtual void update(float deltaTime) override;
	virtual void render(ShaderProgram& shaderProgram) override;

public: // Interfaces
	virtual void write(QJsonObject& json) const override;
	virtual void read(const QJsonObject& json) override;
	virtual void* accept(INodeVisitor* visitor) override;

signals:
	void meshChanged(Mesh* mesh, bool isInstance);
	void polygonModeChanged(PolygonMode polygonMode);
	void drawBufferModeChanged(DrawBufferMode drawBufferMode);


protected:
	bool mIsInstanced;
	
	Mesh* mMesh;
	Material* mMaterial;

	PolygonMode mPolygonMode;
	DrawBufferMode mDrawBufferMode;
};

#endif // !MESH_RENDERER_H