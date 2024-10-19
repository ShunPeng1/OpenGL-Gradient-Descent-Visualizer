#include "Engine/Scenes/Scene.h"
#include "Engine/Scenes/GameObject.h"
#include "Engine/Scenes/Component.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::addMesh(Mesh* mesh)
{
	mMeshes.push_back(mesh);
}

void Scene::addGameObject(GameObject* gameObject)
{
}

void Scene::addComponent(Component* component)
{
}

void Scene::removeMesh(Mesh* mesh)
{
}

void Scene::removeGameObject(GameObject* gameObject)
{
}

void Scene::removeComponent(Component* component)
{
}
