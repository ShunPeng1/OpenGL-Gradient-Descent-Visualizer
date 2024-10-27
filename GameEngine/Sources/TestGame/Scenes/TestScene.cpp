#include "TestGame/Scenes/TestScene.h"

TestScene::TestScene() : Scene()
{
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


    std::shared_ptr<MeshRenderer> teapotNode = std::make_shared<MeshRenderer>(teapot);
	std::shared_ptr<MeshRenderer> triangleNode = std::make_shared<MeshRenderer>(triangle);
	std::shared_ptr<MeshRenderer> quadNode = std::make_shared<MeshRenderer>(quad);
	std::shared_ptr<MeshRenderer> circleNode = std::make_shared<MeshRenderer>(circle);
	std::shared_ptr<MeshRenderer> cubeNode = std::make_shared<MeshRenderer>(cube);
	std::shared_ptr<MeshRenderer> sphereNode = std::make_shared<MeshRenderer>(sphere);
	std::shared_ptr<MeshRenderer> icosphereNode = std::make_shared<MeshRenderer>(icosphere);
	std::shared_ptr<MeshRenderer> cylinderNode = std::make_shared<MeshRenderer>(cylinder);
	std::shared_ptr<MeshRenderer> coneNode = std::make_shared<MeshRenderer>(cone);
	std::shared_ptr<MeshRenderer> planeNode = std::make_shared<MeshRenderer>(plane);

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


	addToUpdateList(teapotNode);
	addToUpdateList(triangleNode);
	addToUpdateList(quadNode);
	addToUpdateList(circleNode);
	addToUpdateList(cubeNode);
	addToUpdateList(sphereNode);
	addToUpdateList(icosphereNode);
	addToUpdateList(cylinderNode);
	addToUpdateList(coneNode);
	addToUpdateList(planeNode);

	addToRenderList(teapotNode);
	addToRenderList(triangleNode);
	addToRenderList(quadNode);
	addToRenderList(circleNode);
	addToRenderList(cubeNode);
	addToRenderList(sphereNode);
	addToRenderList(icosphereNode);
	addToRenderList(cylinderNode);
	addToRenderList(coneNode);
	addToRenderList(planeNode);



	QMatrix4x4 world;
	world.setToIdentity();
	QMatrix4x4 proj = camera->getProjectionMatrix();
	QVector2D texScale(1.0f, 1.0f);

}

TestScene::~TestScene()
{
	delete camera;
}

void TestScene::load()
{
}

void TestScene::init()
{
	Scene::init();
}

