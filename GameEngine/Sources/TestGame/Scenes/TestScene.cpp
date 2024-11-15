#include "TestGame/Scenes/TestScene.h"

#include "Engine/Nodes/GradientDescent.h"

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

	const int numCameras = 10; // Number of cameras
	const float radius = 10.0f; // Radius of the sphere
	const QVector3D center(0.0f, -6.0f, 0.0f); // Center of the sphere

	for (int i = 0; i < numCameras; ++i)
	{
		float theta = M_PI * (i + 1) / (numCameras + 1); // Latitude
		float phi = 2 * M_PI * i / numCameras; // Longitude

		float x = radius * sin(theta) * cos(phi);
		float y = radius * cos(theta);
		float z = radius * sin(theta) * sin(phi);

		Camera* camera = new Camera();
		addNode(camera);
		camera->setObjectName("Camera " + std::to_string(i + 3));
		camera->transform->setLocalPosition(QVector3D(x, y, z));

		// Look at the center
		camera->transform->setLocalRotation(QQuaternion::rotationTo(camera->transform->getLocalPosition(), center - camera->transform->getLocalPosition()));
	}


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

	addMesh(teapot);
	addMesh(triangle);
	addMesh(quad);
	addMesh(circle);
	addMesh(cube);
	addMesh(sphere);
	addMesh(icosphere);
	addMesh(cylinder);
	addMesh(cone);


	MeshRenderer* teapotNode = new MeshRenderer(teapot, true);
	MeshRenderer* triangleNode = new MeshRenderer(triangle, true);
	MeshRenderer* quadNode = new MeshRenderer(quad, true);
	MeshRenderer* circleNode = new MeshRenderer(circle, true);
	MeshRenderer* cubeNode = new MeshRenderer(cube, true);
	MeshRenderer* sphereNode = new MeshRenderer(sphere, true);
	MeshRenderer* icosphereNode = new MeshRenderer(icosphere, true);
	MeshRenderer* cylinderNode = new MeshRenderer(cylinder, true);
	MeshRenderer* coneNode = new MeshRenderer(cone, true);
	MeshRenderer* planeNode = new GradientDescent("Math.sin($x) * Math.sin($y)", -10.0f, 10.0f, 0.1f, -10.0f, 10.0f, 0.1f, 1000, 0.01f, 10, 1);
	MeshRenderer* planeNode2 = new GradientDescent("Math.sin($x**2 - $y**2) / 5 + ($x**2 + $y**2) / 50 - 0.1 * Math.cos(2 * Math.PI * $x) * Math.sin(2 * Math.PI * $y) + 0.5 * Math.exp(-(($x - 2)**2 + ($y - 2)**2))", -10.0f, 10.0f, 0.1f, -10.0f, 10.0f, 0.1f, 1000, 0.01f, 10, 1);
	planeNode2->kill();

	teapotNode->transform->setLocalPosition(QVector3D(-15.0f, 0.0f, 0.0f));
	triangleNode->transform->setLocalPosition(QVector3D(1.0f, 0.0f, 0.0f));
	quadNode->transform->setLocalPosition(QVector3D(3.0f, 0.0f, 0.0f));
	circleNode->transform->setLocalPosition(QVector3D(5.0f, 0.0f, 0.0f));
	cubeNode->transform->setLocalPosition(QVector3D(7.0f, 0.0f, 0.0f));
	sphereNode->transform->setLocalPosition(QVector3D(9.0f, 0.0f, 0.0f));
	icosphereNode->transform->setLocalPosition(QVector3D(11.0f, 0.0f, 0.0f));
	cylinderNode->transform->setLocalPosition(QVector3D(13.0f, 0.0f, 0.0f));
	coneNode->transform->setLocalPosition(QVector3D(15.0f, 0.0f, 0.0f));

	planeNode->transform->setLocalPosition(QVector3D(0.0f, -3.0f, 0.0f));
	planeNode->transform->setLocalRotation(QQuaternion::fromEulerAngles(-90.0f, 0.0f, 0.0f));
	planeNode2->transform->setLocalPosition(QVector3D(0.0f, -8.0f, 0.0f));
	planeNode2->transform->setLocalRotation(QQuaternion::fromEulerAngles(-90.0f, 0.0f, 0.0f));

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
	planeNode2->setObjectName("Plane2");


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
	addNode(planeNode2);

}

void TestScene::create()
{
	Scene::create();

}

TestScene::~TestScene()
{
	delete mCameraController;
}



