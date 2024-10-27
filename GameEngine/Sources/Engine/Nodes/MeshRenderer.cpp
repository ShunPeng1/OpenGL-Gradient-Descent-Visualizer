
#include "Engine/Nodes/MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
	mPolygonMode = PolygonMode::FILL;
	mDrawBufferMode = DrawBufferMode::FRONT_AND_BACK;
}

MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> meshID)
{
	mMesh = meshID;
	mPolygonMode = PolygonMode::FILL;
	mDrawBufferMode = DrawBufferMode::FRONT_AND_BACK;
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

void MeshRenderer::init(Scene* scene)
{
	initializeOpenGLFunctions();
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