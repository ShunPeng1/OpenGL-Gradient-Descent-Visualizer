#include "TestGame/Scenes/TestScene.h"

TestScene::TestScene() : Scene()
{
	setName("TestScene");
}

void TestScene::load()
{
	Scene::load();


	Camera* camera = new Camera();
	addNode(camera);
	camera->setObjectName("Camera 1");


	Camera* camera2 = new Camera();
	addNode(camera2);
	camera2->setObjectName("Camera 2");
	camera2->transform->setLocalPosition(QVector3D(0.0f, 0.0f, 10.0f));

	mCameraController = new FPSCameraController(camera);
	inputPublisher->subscribe(mCameraController);


	ModelLoader tempLoader = ModelLoader::Builder().SetUseNormalColor(true).Build();

	Mesh* teapot = tempLoader.loadObjFile(":/Resources/Models/teapot.obj");
	Mesh* triangle = tempLoader.loadTriangle();
	Mesh* quad = tempLoader.loadQuad();
	Mesh* circle = tempLoader.loadCircle(36);
	Mesh* cube = tempLoader.loadCube();
	Mesh* sphere = tempLoader.loadSphere(40, 40);
	Mesh* icosphere = tempLoader.loadIcosphere(5);
	Mesh* cylinder = tempLoader.loadCylinder(36);
	Mesh* cone = tempLoader.loadCone(36);

	ModelLoader::Range xRange = ModelLoader::Range(-10.0f, 10.0f, 0.1f);
	ModelLoader::Range yRange = ModelLoader::Range(-10.0f, 10.0f, 0.1f);
	Mesh* plane = tempLoader.loadPlane([](float x, float y) -> float {
		return std::sin(x) * std::sin(y);
		}, xRange, yRange);


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


	MeshRenderer* teapotNode = new MeshRenderer(teapot, true);
	MeshRenderer* triangleNode = new MeshRenderer(triangle, true);
	MeshRenderer* quadNode = new MeshRenderer(quad, true);
	MeshRenderer* circleNode = new MeshRenderer(circle, true);
	MeshRenderer* cubeNode = new MeshRenderer(cube, true);
	MeshRenderer* sphereNode = new MeshRenderer(sphere, true);
	MeshRenderer* icosphereNode = new MeshRenderer(icosphere, true);
	MeshRenderer* cylinderNode = new MeshRenderer(cylinder, true);
	MeshRenderer* coneNode = new MeshRenderer(cone, true);
	MeshRenderer* planeNode = new MeshRenderer(plane, true);

	teapotNode->transform->setLocalPosition(QVector3D(-15.0f, 0.0f, 0.0f));
	triangleNode->transform->setLocalPosition(QVector3D(1.0f, 0.0f, 0.0f));
	quadNode->transform->setLocalPosition(QVector3D(3.0f, 0.0f, 0.0f));
	circleNode->transform->setLocalPosition(QVector3D(5.0f, 0.0f, 0.0f));
	cubeNode->transform->setLocalPosition(QVector3D(7.0f, 0.0f, 0.0f));
	sphereNode->transform->setLocalPosition(QVector3D(9.0f, 0.0f, 0.0f));
	icosphereNode->transform->setLocalPosition(QVector3D(11.0f, 0.0f, 0.0f));
	cylinderNode->transform->setLocalPosition(QVector3D(13.0f, 0.0f, 0.0f));
	coneNode->transform->setLocalPosition(QVector3D(15.0f, 0.0f, 0.0f));
	planeNode->transform->setLocalPosition(QVector3D(0.0f, 0.0f, 2.0f));

	teapotNode->setObjectName("Teapot");
	triangleNode->setObjectName("Triangle");
	quadNode->setObjectName("Quad");
	circleNode->setObjectName("Circle");
	cubeNode->setObjectName("Cube");
	sphereNode->setObjectName("Sphere");
	icosphereNode->setObjectName("Icosphere");
	cylinderNode->setObjectName("Cylinder");
	coneNode->setObjectName("Cone");
	planeNode->setObjectName("Plane");


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

void TestScene::create()
{
	Scene::create();

}

TestScene::~TestScene()
{
	delete mCameraController;
}



