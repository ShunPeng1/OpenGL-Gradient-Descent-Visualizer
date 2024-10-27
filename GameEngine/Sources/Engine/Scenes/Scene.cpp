#include "Engine/Scenes/Scene.h"

Scene::Scene()
{
	mMeshes = std::vector<std::shared_ptr<Mesh>>();
	mUpdateLists = std::vector<std::shared_ptr<Node>>();
	mRenderLists = std::vector<std::shared_ptr<Node>>();

	inputPublisher = new InputPublisher();
	camera = new Camera();
}

Scene::~Scene()
{

}

void Scene::init()
{

	ShaderProgram *defaultShader = new ShaderProgram(":/Resources/Shaders/default.vert", ":/Resources/Shaders/default.frag");
	mDefaultShader = std::shared_ptr<ShaderProgram>(defaultShader);
	mDefaultShader->bind();
	mDefaultShader->setUniformValue("mProjection", camera->getProjectionMatrix());
	mDefaultShader->setUniformValue("mView", camera->getViewMatrix()); 
	mDefaultShader->setUniformValue("mUseTexture", false);
	mDefaultShader->setUniformValue("mUseColor", true);
	mDefaultShader->release();


	for (auto& mesh : mMeshes)
	{
		mesh->init();
	}

	for (auto& node : mUpdateLists)
	{
		node->init(this);
	}

	camera->init(this);
}

void Scene::update(float deltaTime)
{
	for (auto& node : mUpdateLists)
	{
		if (node->getIsAlive()) 
		{
			node->update(deltaTime);
		}
	}
}

void Scene::render()
{
	mDefaultShader->bind();
	camera->render(*mDefaultShader);

	for (auto& node : mRenderLists)
	{
		if (node->getIsAlive())
		{
			node->render(*mDefaultShader);
		}
	}
	mDefaultShader->release();
}

int Scene::addMesh(std::shared_ptr<Mesh> mesh)
{
	mMeshes.push_back(mesh);
	return mMeshes.size() - 1;
}

void Scene::addToUpdateList(std::shared_ptr<Node> node)
{
	mUpdateLists.push_back(node);
}

void Scene::addToRenderList(std::shared_ptr<Node> node)
{
	mRenderLists.push_back(node);
}

void Scene::removeMesh(std::shared_ptr<Mesh> mesh)
{
	mMeshes.erase(std::remove(mMeshes.begin(), mMeshes.end(), mesh), mMeshes.end());
}

void Scene::removeFromUpdateList(std::shared_ptr<Node> node)
{
	mUpdateLists.erase(std::remove(mUpdateLists.begin(), mUpdateLists.end(), node), mUpdateLists.end());
}

void Scene::removeFromRenderList(std::shared_ptr<Node> node)
{
	mRenderLists.erase(std::remove(mRenderLists.begin(), mRenderLists.end(), node), mRenderLists.end());
}

std::shared_ptr<Mesh> Scene::getMesh(int index) const
{
	return mMeshes[index];
}