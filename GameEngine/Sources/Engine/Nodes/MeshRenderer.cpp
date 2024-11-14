
#include "Engine/Nodes/MeshRenderer.h"


MeshRenderer::MeshRenderer(Mesh* mesh, bool isInstance)
{
	mMesh = mesh;
	mPolygonMode = PolygonMode::FILL;
	mDrawBufferMode = DrawBufferMode::FRONT_AND_BACK;

	mIsInstanced = isInstance;

	setObjectName("Mesh Renderer");
}

void MeshRenderer::init()
{
	initializeOpenGLFunctions();
}

MeshRenderer::~MeshRenderer() noexcept
{
	if (mMesh != nullptr)
	{
		if (!mIsInstanced) {
			delete mMesh;
		}
		mMesh = nullptr;
	}
}

void MeshRenderer::setMesh(Mesh* mesh, bool isInstance)
{
	mMesh = mesh;
	mIsInstanced = isInstance;
}

Mesh* MeshRenderer::getMesh() const
{
	return mMesh;
}

void MeshRenderer::setPolygonMode(PolygonMode polygonMode)
{
	mPolygonMode = polygonMode;
}

void MeshRenderer::setDrawBufferMode(DrawBufferMode drawBufferMode)
{
	mDrawBufferMode = drawBufferMode;
}

PolygonMode MeshRenderer::getPolygonMode() const
{
	return mPolygonMode;
}

DrawBufferMode MeshRenderer::getDrawBufferMode() const
{
	return mDrawBufferMode;
}

void MeshRenderer::start(IScene* scene)
{

}

void MeshRenderer::update(float deltaTime)
{

}

void MeshRenderer::render(ShaderProgram& shaderProgram)
{
	QMatrix4x4 world = transform->getWorldMatrix();
	shaderProgram.setUniformValue("mWorld", world);

	glPolygonMode(static_cast<GLenum>(mDrawBufferMode), static_cast<GLenum>(mPolygonMode));
	mMesh->draw(shaderProgram);

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