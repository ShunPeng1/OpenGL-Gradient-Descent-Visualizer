#include "Engine/Scenes/Scene.h"
#include "Engine/Constants/SerializePath.h"

Scene::Scene()
{
	mMeshes = std::vector<Mesh*>();
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

	for (int i = 0; i < mMeshes.size(); i++)
	{
		mMeshes[i]->init();
	}

	for (int i = 0; i < mChildrenNodes.size(); i++)
	{
		mChildrenNodes[i]->init();
	}

}

void Scene::create()
{

}

void Scene::start()
{
	mDefaultShader->start();

	for (int i = 0; i < mMeshes.size(); i++)
	{
		mMeshes[i]->tryStart();
	}

	for (int i = 0; i < mChildrenNodes.size(); i++)
	{
		mChildrenNodes[i]->tryStart(this);
	}

}

void Scene::update(float deltaTime)
{
	
	for (int i = 0; i < mChildrenNodes.size(); i++)
	{
		mChildrenNodes[i]->tryUpdate(deltaTime);
	}
}

void Scene::render()
{
	mDefaultShader->bind();

	mMainCamera->tryRender(*mDefaultShader); // Only render the main camera

	for (int i = 0; i < mChildrenNodes.size(); i++)
	{
		Node* node = mChildrenNodes[i].get();
		Camera* camera = dynamic_cast<Camera*>(node);
		if (camera != nullptr) { // Skip camera nodes
			continue;
		}

		node->tryRender(*mDefaultShader);
	}

	mDefaultShader->release();
}

void Scene::clear()
{
	for (int i = 0; i < mMeshes.size(); i++)
	{
		mMeshes[i]->clear();
	}

	for (int i = 0; i < mChildrenNodes.size(); i++)
	{
		Node* node = mChildrenNodes[i].get();
		node->clear();
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
		Mesh* mesh = new Mesh();
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

int Scene::addMesh(Mesh* mesh)
{
	mMeshes.push_back(mesh);
	return static_cast<int>(mMeshes.size()) - 1;
}

void Scene::removeMesh(Mesh* mesh)
{
	mMeshes.erase(std::remove(mMeshes.begin(), mMeshes.end(), mesh), mMeshes.end());
}

Mesh* Scene::getMesh(int index) const
{
	if (index < 0 || index >= mMeshes.size()) {
		return nullptr;
	}

	return mMeshes[index];
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

	mChildrenNodes.push_back(std::unique_ptr<Node>(node));
	

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
