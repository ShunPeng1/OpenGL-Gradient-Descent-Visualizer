#include "Engine/Scenes/Scene.h"
#include "Engine/Constants/SerializePath.h"

Scene::Scene()
{
	mMeshes = std::vector<std::shared_ptr<Mesh>>();
	mChildrenNodes = std::vector<std::unique_ptr<Node>>();
}

Scene::~Scene()
{
}

void Scene::load()
{
	ShaderProgram* defaultShader = new ShaderProgram(":/Resources/Shaders/default.vert", ":/Resources/Shaders/default.frag");
	mDefaultShader = std::shared_ptr<ShaderProgram>(defaultShader);

	// Input publisher
	inputPublisher = new InputPublisher();
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

	for (auto& camera : mCameras)
	{
		camera->init();
	}
}

void Scene::create()
{

}

void Scene::start()
{
	mDefaultShader->start();

	for (auto& mesh : mMeshes)
	{
		mesh->tryStart();
	}

	for (auto& node : mChildrenNodes)
	{
		node->tryStart(this);
	}

	for (auto& camera : mCameras)
	{
		camera->tryStart(this);
	}
}

void Scene::update(float deltaTime)
{
	for (auto& node : mChildrenNodes)
	{
		node->tryUpdate(deltaTime);
	}

	for (auto& camera : mCameras)
	{
		camera->tryUpdate(deltaTime);
	}
}

void Scene::render()
{
	mDefaultShader->bind();

	mMainCamera->tryRender(*mDefaultShader); // Only render the main camera

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

	for (auto& camera : mCameras)
	{
		camera->clear();
	}

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
	return static_cast<int>(mMeshes.size()) - 1;
}

void Scene::removeMesh(std::shared_ptr<Mesh> mesh)
{
	mMeshes.erase(std::remove(mMeshes.begin(), mMeshes.end(), mesh), mMeshes.end());
}

void Scene::addNode(Node* node)
{
	Camera* camera = dynamic_cast<Camera*>(node);
	if (camera != nullptr) {
		if (mMainCamera == nullptr) {
			mMainCamera = camera;
		}
		mCameras.push_back(camera);
	}
	else {
		mChildrenNodes.push_back(std::unique_ptr<Node>(node));
	}

}

void Scene::removeNode(Node* node)
{
	Camera* camera = dynamic_cast<Camera*>(node);

	if (camera != nullptr) {
		auto it = std::remove(mCameras.begin(), mCameras.end(), camera);
		if (it != mCameras.end()) {
			mCameras.erase(it, mCameras.end());
		}

		if (mMainCamera == camera) {
			mMainCamera = mCameras.size() > 0 ? mCameras[0] : nullptr;
		}
	}
	else {
		auto it = std::remove_if(mChildrenNodes.begin(), mChildrenNodes.end(),
			[node](const std::unique_ptr<Node>& ptr) {
				return ptr.get() == node;
			});
		if (it != mChildrenNodes.end()) {
			mChildrenNodes.erase(it, mChildrenNodes.end());
		}
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

std::vector<Camera*> Scene::getCameras()
{
	return mCameras;
}

void Scene::setMainCamera(Camera* camera)
{
	mMainCamera = camera;
}

void Scene::setInputPublisher(InputPublisher* inputPublisher)
{
	this->inputPublisher = inputPublisher;
}

InputPublisher* Scene::getInputPublisher() const
{
	return this->inputPublisher;
}

std::shared_ptr<Mesh> Scene::getMesh(int index) const
{
	return mMeshes[index];
}