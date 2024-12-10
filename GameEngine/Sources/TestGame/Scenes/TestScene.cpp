#include "TestGame/Scenes/TestScene.h"

#include "Engine/Nodes/GradientDescent.h"


static QQuaternion CreateFromAxisAngle(const QVector3D& axis, float angle)
{
	float halfAngle = angle * 0.5f;
	float s = std::sin(halfAngle);
	return QQuaternion(std::cos(halfAngle), axis.x() * s, axis.y() * s, axis.z() * s);
}

static QQuaternion LookAt(const QVector3D& sourcePoint, const QVector3D& destPoint)
{
	QVector3D forwardVector = (destPoint - sourcePoint).normalized();
	QVector3D forward(0.0f, 0.0f, -1.0f);

	float dot = QVector3D::dotProduct(forward, forwardVector);

	if (std::abs(dot - (-1.0f)) < 0.000001f)
	{
		return QQuaternion(0.0f, 1.0f, 0.0f, 3.1415926535897932f);
	}
	if (std::abs(dot - (1.0f)) < 0.000001f)
	{
		return QQuaternion();
	}

	float rotAngle = std::acos(dot);
	QVector3D rotAxis = QVector3D::crossProduct(forward, forwardVector).normalized();
	return CreateFromAxisAngle(rotAxis, rotAngle);
}

TestScene::TestScene() : Scene()
{
	setName("TestScene");
}

void TestScene::load()
{
	Scene::load();


	Camera* camera = new Camera();
	addNode(camera);
	mCameraManager->addCamera(camera);
	camera->setObjectName("Camera 1");



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
	

	teapotNode->transform->setLocalPosition(QVector3D(-15.0f, 0.0f, 0.0f));
	triangleNode->transform->setLocalPosition(QVector3D(1.0f, 0.0f, 0.0f));
	quadNode->transform->setLocalPosition(QVector3D(3.0f, 0.0f, 0.0f));
	circleNode->transform->setLocalPosition(QVector3D(5.0f, 0.0f, 0.0f));
	cubeNode->transform->setLocalPosition(QVector3D(7.0f, 0.0f, 0.0f));
	sphereNode->transform->setLocalPosition(QVector3D(9.0f, 0.0f, 0.0f));
	icosphereNode->transform->setLocalPosition(QVector3D(11.0f, 0.0f, 0.0f));
	cylinderNode->transform->setLocalPosition(QVector3D(13.0f, 0.0f, 0.0f));
	coneNode->transform->setLocalPosition(QVector3D(15.0f, 0.0f, 0.0f));


	teapotNode->setObjectName("Teapot");
	triangleNode->setObjectName("Triangle");
	quadNode->setObjectName("Quad");
	circleNode->setObjectName("Circle");
	cubeNode->setObjectName("Cube");
	sphereNode->setObjectName("Sphere");
	icosphereNode->setObjectName("Icosphere");
	cylinderNode->setObjectName("Cylinder");
	coneNode->setObjectName("Cone");

	addNode(teapotNode);
	addNode(triangleNode);
	addNode(quadNode);
	addNode(circleNode);
	addNode(cubeNode);
	addNode(sphereNode);
	addNode(icosphereNode);
	addNode(cylinderNode);
	addNode(coneNode);	

	
	for (int i = 0; i < 0; i++) {

		GradientDescent* planeNode1 = new GradientDescent("Math.sin($x) * Math.cos($y) + Math.cos(Math.sqrt($x * $x + $y * $y)) * Math.sin($x * $y)", -5.0f, 5.0f, 0.01f, -5.0f, 5.0f, 0.01f);
		planeNode1->transform->setLocalPosition(QVector3D(0.0f, -3.0f, 0.0f));
		planeNode1->transform->setLocalRotation(QQuaternion::fromEulerAngles(-90.0f, 0.0f, 0.0f));
		planeNode1->setObjectName("Plane " + std::to_string(i));
		planeNode1->setPointCount(100);
		// Set the method for the GradientDescent node
		switch (i) {
		case 0:
			planeNode1->setMethod(GradientDescent::Method::SGD);
			break;
		case 1:
			planeNode1->setMethod(GradientDescent::Method::Momentum);
			break;
		case 2:
			planeNode1->setMethod(GradientDescent::Method::NesterovMomentum);
			break;
		case 3:
			planeNode1->setMethod(GradientDescent::Method::AdaGrad);
			break;
		case 4:
			planeNode1->setMethod(GradientDescent::Method::RMSProp);
			break;
		case 5:
			planeNode1->setMethod(GradientDescent::Method::Adam);
			break;
		}
		addNode(planeNode1);
	}


	const int numLatitude = 10; // Number of latitude divisions
	const int numLongitude = 10; // Number of longitude divisions
	const float radius = 10.0f; // Radius of the sphere
	const QVector3D center(0.0f, 0.0f, 0.0f); // Center of the sphere

	Container* sphereContainer = new Container();
	addNode(sphereContainer);

	// Create cameras on a sphere
	Camera* topCamera = new Camera();
	topCamera->setParent(sphereContainer);
	mCameraManager->addCamera(topCamera);
	topCamera->setObjectName("Top Camera");
	topCamera->transform->setLocalPosition(QVector3D(0, radius, 0));
	topCamera->transform->setLocalRotation(LookAt(topCamera->transform->getLocalPosition(), center));

	for (int i = 1; i < numLatitude; ++i) {
		// Latitude: range from 0 (north pole) to pi (south pole)
		float theta = M_PI * i / (numLatitude - 1);

		for (int j = 0; j < numLongitude; ++j) {
			// Longitude: range from 0 to 2*pi
			float phi = 2 * M_PI * j / numLongitude;

			float x = radius * sin(theta) * cos(phi);
			float y = radius * cos(theta);  // Moves from pole (1) to equator (0)
			float z = radius * sin(theta) * sin(phi);


			Camera* camera = new Camera();
			camera->setParent(sphereContainer);
			mCameraManager->addCamera(camera);

			camera->setObjectName(QString("Camera %1 %2").arg(i).arg(j));
			camera->transform->setLocalPosition(QVector3D(x, y, z));

			// Look at the center
			camera->transform->setLocalRotation(LookAt(camera->transform->getLocalPosition(), center));
		}
	}

	sphereContainer->transform->setWorldPosition(teapotNode->transform->getWorldPosition());
	teapotNode->setParent(sphereContainer);
}

void TestScene::create()
{
	Scene::create();

}

TestScene::~TestScene()
{
	delete mCameraController;
}


