#include "Engine/Scenes/Scene.h"
#include "Engine/Scenes/GameObject.h"
#include "Engine/Scenes/Component.h"

Scene::Scene()
{
	mMeshes = std::vector<std::shared_ptr<Mesh>>();
	mUpdateLists = std::vector<std::shared_ptr<GameObject>>();
	mRenderLists = std::vector<std::shared_ptr<GameObject>>();
}

Scene::~Scene()
{

}

void Scene::update(float deltaTime)
{
	for (auto& gameObject : mUpdateLists)
	{
		if (gameObject->getIsAlive()) 
		{
			gameObject->update(deltaTime);
		}
	}
}

void Scene::render()
{
	mDefaultShader->bind();
	for (auto& gameObject : mRenderLists)
	{
		if (gameObject->getIsAlive())
		{
			gameObject->render(*mDefaultShader);
		}
	}
	mDefaultShader->release();
}

int Scene::addMesh(std::shared_ptr<Mesh> mesh)
{
	mMeshes.push_back(mesh);
	return mMeshes.size() - 1;
}

void Scene::addToUpdateList(std::shared_ptr<GameObject> gameObject)
{
	mUpdateLists.push_back(gameObject);
}

void Scene::addToRenderList(std::shared_ptr<GameObject> gameObject)
{
	mRenderLists.push_back(gameObject);
}

void Scene::removeMesh(std::shared_ptr<Mesh> mesh)
{
	mMeshes.erase(std::remove(mMeshes.begin(), mMeshes.end(), mesh), mMeshes.end());
}

void Scene::removeFromUpdateList(std::shared_ptr<GameObject> gameObject)
{
	mUpdateLists.erase(std::remove(mUpdateLists.begin(), mUpdateLists.end(), gameObject), mUpdateLists.end());
}

void Scene::removeFromRenderList(std::shared_ptr<GameObject> gameObject)
{
	mRenderLists.erase(std::remove(mRenderLists.begin(), mRenderLists.end(), gameObject), mRenderLists.end());
}

std::shared_ptr<Mesh> Scene::getMesh(int index) const
{
	return mMeshes[index];
}