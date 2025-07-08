
#include "Engine/Nodes/MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
	mMesh = nullptr;
	mPolygonMode = PolygonMode::FILL;
	mDrawBufferMode = DrawBufferMode::FRONT_AND_BACK;

	mIsInstanced = false;

	setObjectName("Mesh Renderer");
}

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material, bool isInstance)
{
	mMesh = mesh;
	mMaterial = material;
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

	emit meshChanged(mesh, isInstance);
}

Mesh* MeshRenderer::getMesh() const
{
	return mMesh;
}

void MeshRenderer::setMaterial(Material* material)
{
	mMaterial = material;
}

Material* MeshRenderer::getMaterial()
{
	return mMaterial;
}

void MeshRenderer::setPolygonMode(PolygonMode polygonMode)
{
	mPolygonMode = polygonMode;
	emit polygonModeChanged(polygonMode);
}

void MeshRenderer::setDrawBufferMode(DrawBufferMode drawBufferMode)
{
	mDrawBufferMode = drawBufferMode;
	emit drawBufferModeChanged(drawBufferMode);
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
	
	if (mMaterial) {
		shaderProgram.setUniformValue("mMaterial", mMaterial->getMaterial());
		shaderProgram.setUniformValue("mColorFactor", mMaterial->getColorFactor());
		shaderProgram.setUniformValue("mTextureFactor", mMaterial->getTextureFactor());
		shaderProgram.setUniformValue("mPhongFactor", mMaterial->getPhongFactor());
		shaderProgram.setUniformValue("mShininess", mMaterial->getShininess());
	}

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