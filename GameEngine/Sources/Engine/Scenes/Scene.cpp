#include "Engine/Scenes/Scene.h"
#include "Engine/Constants/SerializePath.h"

Scene::Scene()
{
	mMeshes = std::vector<std::shared_ptr<Mesh>>();
	mChildrenNodes = std::vector<std::unique_ptr<Node>>();

	camera = new Camera();
}

Scene::~Scene()
{
}

void Scene::load()
{
	ShaderProgram* defaultShader = new ShaderProgram(":/Resources/Shaders/default.vert", ":/Resources/Shaders/default.frag");
	mDefaultShader = std::shared_ptr<ShaderProgram>(defaultShader);

}

void Scene::init()
{
	mDefaultShader->init();

	for (auto& mesh : mMeshes)
	{
		mesh->init();
	}

	for (auto& node : mChildrenNodes)
	{
		node->init();
	}

	camera->init();
	
}

void Scene::create()
{
	// Bind attribute locations before linking
	mDefaultShader->bindAttributeLocation("position", 0);
	mDefaultShader->bindAttributeLocation("normal", 1);
	mDefaultShader->bindAttributeLocation("texCoord", 2);
	mDefaultShader->bindAttributeLocation("color", 3);

	mDefaultShader->start();
	mDefaultShader->bind();
	mDefaultShader->setUniformValue("mUseTexture", false);
	mDefaultShader->setUniformValue("mUseColor", true);
	mDefaultShader->release();
}

void Scene::start()
{

	for (auto& mesh : mMeshes)
	{
		mesh->tryStart();
	}

	for (auto& node : mChildrenNodes)
	{
		node->tryStart(this);
	}

	camera->tryStart(this);
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

void Scene::clear()
{
	for (auto& mesh : mMeshes)
	{
		mesh->clear();
	}

	for (auto& node : mChildrenNodes)
	{
		node->clear();
	}

	camera->clear();

	mDefaultShader->clear();
}

IScene* Scene::clone() const
{
	Scene* scene = new Scene();
	scene->mMeshes = mMeshes;

	scene->inputPublisher = inputPublisher;

	return scene;
}

void Scene::write(QJsonObject& json) const {
	QJsonArray nodesArray;
	for (const auto& node : mChildrenNodes) {
		QJsonObject nodeObject;
		node->write(nodeObject);
		nodesArray.append(nodeObject);
	}
	json[SERIALIZE_SCENE_NODES] = nodesArray;

	QJsonArray meshesArray;
	for (const auto& mesh : mMeshes) {
		QJsonObject meshObject;
		// Assuming Mesh class has a write method
		mesh->write(meshObject);
		meshesArray.append(meshObject);
	}
	json[SERIALIZE_SCENE_MESHES] = meshesArray;


}

void Scene::read(const QJsonObject& json) {

	mMeshes.clear();
	QJsonArray meshesArray = json[SERIALIZE_SCENE_MESHES].toArray();
	for (int i = 0; i < meshesArray.size(); ++i) {
		QJsonObject meshObject = meshesArray[i].toObject();
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		// Assuming Mesh class has a read method
		mesh->read(meshObject);
		addMesh(mesh);
	}

	mChildrenNodes.clear();
	QJsonArray nodesArray = json[SERIALIZE_SCENE_NODES].toArray();
	for (int i = 0; i < nodesArray.size(); ++i) {
		QJsonObject nodeObject = nodesArray[i].toObject();
		std::unique_ptr<Node> node = std::make_unique<Node>();
		node->read(nodeObject);
		addNode(node.release());
	}


	// Deserialize other properties if needed
}

QString Scene::getName() const
{
	return mName;
}

void Scene::setName(const QString& name)
{
	mName = name;
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

std::vector<Node*> Scene::getNodes() const
{
	std::vector<Node*> children;
	for (const auto& child : mChildrenNodes)
	{
		children.push_back(child.get());
	}

	return children;
}

void Scene::setInputPublisher(InputPublisher* inputPublisher)
{
	this->inputPublisher = inputPublisher;
}

InputPublisher* Scene::getInputPublisher() const
{
	return this->inputPublisher;
}

void Scene::setCamera(Camera* camera)
{
	this->camera = camera;
}

Camera* Scene::getCamera() const
{
	return this->camera;
}

std::shared_ptr<Mesh> Scene::getMesh(int index) const
{
	return mMeshes[index];
}