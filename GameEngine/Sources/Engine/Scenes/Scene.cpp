#include "Engine/Scenes/Scene.h"

Scene::Scene()
{
	mMeshes = std::vector<std::shared_ptr<Mesh>>();
	mChildrenNodes = std::vector<std::unique_ptr<Node>>();



	inputPublisher = new InputPublisher();
	camera = new Camera();
}

Scene::~Scene()
{
}

void Scene::load()
{
}

void Scene::create()
{
	ShaderProgram* defaultShader = new ShaderProgram(":/Resources/Shaders/default.vert", ":/Resources/Shaders/default.frag");
	mDefaultShader = std::shared_ptr<ShaderProgram>(defaultShader);
	mDefaultShader->bind();
	mDefaultShader->setUniformValue("mProjection", camera->getProjectionMatrix());
	mDefaultShader->setUniformValue("mView", camera->getViewMatrix());
	mDefaultShader->setUniformValue("mUseTexture", false);
	mDefaultShader->setUniformValue("mUseColor", true);
	mDefaultShader->release();
}

void Scene::init()
{
	

	for (auto& node : mChildrenNodes)
	{
		node->tryInit(this);
	}

	for (auto& mesh : mMeshes)
	{
		mesh->init();
	}

	camera->tryInit(this);
}

void Scene::update(float deltaTime)
{
	camera->tryUpdate(deltaTime);
	for (auto& node : mChildrenNodes)
	{
		node->tryUpdate(deltaTime);
	}
}

void Scene::render()
{
	mDefaultShader->bind();
	camera->tryRender(*mDefaultShader);

	for (auto& node : mChildrenNodes)
	{
		node->tryRender(*mDefaultShader);
	}
	mDefaultShader->release();
}

int Scene::addMesh(std::shared_ptr<Mesh> mesh)
{
	mMeshes.push_back(mesh);
	return mMeshes.size() - 1;
}

void Scene::removeMesh(std::shared_ptr<Mesh> mesh)
{
	mMeshes.erase(std::remove(mMeshes.begin(), mMeshes.end(), mesh), mMeshes.end());
}

void Scene::addNode(Node* node)
{
	mChildrenNodes.push_back(std::unique_ptr<Node>(node));
}

void Scene::removeNode(Node* node)
{
	auto it = std::remove_if(mChildrenNodes.begin(), mChildrenNodes.end(),
		[node](const std::unique_ptr<Node>& ptr) {
			return ptr.get() == node;
		});
	if (it != mChildrenNodes.end()) {
		mChildrenNodes.erase(it, mChildrenNodes.end());
	}
}

std::shared_ptr<Mesh> Scene::getMesh(int index) const
{
	return mMeshes[index];
}