
#include "Engine/Nodes/MeshRenderer.h"

MeshRenderer::MeshRenderer() : Container()
{
	mPolygonMode = PolygonMode::FILL;
	mDrawBufferMode = DrawBufferMode::FRONT_AND_BACK;

	setName("Mesh Renderer");
}

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> meshID) : Container()
{
	mMesh = meshID;
	mPolygonMode = PolygonMode::FILL;
	mDrawBufferMode = DrawBufferMode::FRONT_AND_BACK;

	setName("Mesh Renderer");
}

void MeshRenderer::init()
{
	initializeOpenGLFunctions();
}

MeshRenderer::~MeshRenderer() noexcept
{
}

void MeshRenderer::setMesh(std::shared_ptr<Mesh> mesh)
{
	mMesh = mesh;
}

std::shared_ptr<Mesh> MeshRenderer::getMesh() const
{
	return mMesh;
}

void MeshRenderer::setRenderMode(PolygonMode polygonMode, DrawBufferMode drawBufferMode)
{
	mPolygonMode = polygonMode;
	mDrawBufferMode = drawBufferMode;
}

void MeshRenderer::start(IScene* scene)
{
}

void MeshRenderer::update(float deltaTime)
{

}

void MeshRenderer::render(ShaderProgram& shaderProgram)
{
	QMatrix4x4 world = transform.getWorldMatrix();
	shaderProgram.setUniformValue("mWorld", world);

	mMesh->draw(shaderProgram);

	glPolygonMode(static_cast<GLenum>(mDrawBufferMode), static_cast<GLenum>(mPolygonMode));
}

void MeshRenderer::write(QJsonObject& json) const
{
}

void MeshRenderer::read(const QJsonObject& json)
{
}

void* MeshRenderer::accept(INodeVisitor* visitor)
{
	return visitor->visitMeshRenderer(this);
}