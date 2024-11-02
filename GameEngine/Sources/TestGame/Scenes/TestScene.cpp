#include "TestGame/Scenes/TestScene.h"

TestScene::TestScene() : Scene()
{
	
}

void TestScene::load()
{
	Scene::load();

	mCameraController = new FPSCameraController(camera);
	inputPublisher->subscribe(mCameraController);

	ModelLoader tempLoader = ModelLoader::Builder().SetUseNormalColor(true).Build();

	std::shared_ptr<Mesh> teapot = std::shared_ptr<Mesh>(tempLoader.loadObjFile(":/Resources/Models/teapot.obj"));
	std::shared_ptr<Mesh> triangle = std::shared_ptr<Mesh>(tempLoader.loadTriangle());
	std::shared_ptr<Mesh> quad = std::shared_ptr<Mesh>(tempLoader.loadQuad());
	std::shared_ptr<Mesh> circle = std::shared_ptr<Mesh>(tempLoader.loadCircle(36));
	std::shared_ptr<Mesh> cube = std::shared_ptr<Mesh>(tempLoader.loadCube());
	std::shared_ptr<Mesh> sphere = std::shared_ptr<Mesh>(tempLoader.loadSphere(40, 40));
	std::shared_ptr<Mesh> icosphere = std::shared_ptr<Mesh>(tempLoader.loadIcosphere(5));
	std::shared_ptr<Mesh> cylinder = std::shared_ptr<Mesh>(tempLoader.loadCylinder(36));
	std::shared_ptr<Mesh> cone = std::shared_ptr<Mesh>(tempLoader.loadCone(36));

	ModelLoader::Range xRange = ModelLoader::Range(-10.0f, 10.0f, 0.1f);
	ModelLoader::Range yRange = ModelLoader::Range(-10.0f, 10.0f, 0.1f);
	std::shared_ptr<Mesh> plane = std::shared_ptr<Mesh>(tempLoader.loadPlane([](float x, float y) -> float {
		return std::sin(x) * std::sin(y);
		}, xRange, yRange));


	addMesh(teapot);
	addMesh(triangle);
	addMesh(quad);
	addMesh(circle);
	addMesh(cube);
	addMesh(sphere);
	addMesh(icosphere);
	addMesh(cylinder);
	addMesh(cone);
	addMesh(plane);


	MeshRenderer* teapotNode = new MeshRenderer(teapot);
	MeshRenderer* triangleNode = new MeshRenderer(triangle);
	MeshRenderer* quadNode = new MeshRenderer(quad);
	MeshRenderer* circleNode = new MeshRenderer(circle);
	MeshRenderer* cubeNode = new MeshRenderer(cube);
	MeshRenderer* sphereNode = new MeshRenderer(sphere);
	MeshRenderer* icosphereNode = new MeshRenderer(icosphere);
	MeshRenderer* cylinderNode = new MeshRenderer(cylinder);
	MeshRenderer* coneNode = new MeshRenderer(cone);
	MeshRenderer* planeNode = new MeshRenderer(plane);

	teapotNode->transform.setLocalPosition(QVector3D(-15.0f, 0.0f, 0.0f));
	triangleNode->transform.setLocalPosition(QVector3D(1.0f, 0.0f, 0.0f));
	quadNode->transform.setLocalPosition(QVector3D(3.0f, 0.0f, 0.0f));
	circleNode->transform.setLocalPosition(QVector3D(5.0f, 0.0f, 0.0f));
	cubeNode->transform.setLocalPosition(QVector3D(7.0f, 0.0f, 0.0f));
	sphereNode->transform.setLocalPosition(QVector3D(9.0f, 0.0f, 0.0f));
	icosphereNode->transform.setLocalPosition(QVector3D(11.0f, 0.0f, 0.0f));
	cylinderNode->transform.setLocalPosition(QVector3D(13.0f, 0.0f, 0.0f));
	coneNode->transform.setLocalPosition(QVector3D(15.0f, 0.0f, 0.0f));
	planeNode->transform.setLocalPosition(QVector3D(0.0f, 0.0f, 2.0f));

	addNode(teapotNode);
	addNode(triangleNode);
	addNode(quadNode);
	addNode(circleNode);
	addNode(cubeNode);
	addNode(sphereNode);
	addNode(icosphereNode);
	addNode(cylinderNode);
	addNode(coneNode);
	addNode(planeNode);

}

TestScene::~TestScene()
{
	delete camera;
}



