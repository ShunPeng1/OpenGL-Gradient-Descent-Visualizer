#include "Engine/Engine.h"
#include "Engine/Scenes/Scene.h"
#include "Engine/Loaders/ModelLoader.h"
#include "Engine/GameObjects/Camera.h"
#include "TestGame/Controllers/FPSCameraController.h"
#include "Engine/GameObjects/MeshRenderer.h"

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	void load() override;
	void init() override;
	void update(float deltaTime) override;
	void render() override;

private: 
	Camera* camera;
	FPSCameraController* cameraController;


    // Add other models...

    bool firstMouse;
    float deltaTime;
    float lastFrame;
    bool spacePressed;
    int currentModel;

    QElapsedTimer* elapsedTimer;
    QMap<int, bool> keyStates;
};

TestScene::TestScene()
{
	mDefaultShader = std::shared_ptr<ShaderProgram>(new ShaderProgram(":/Resources/Shaders/default.vert", ":/Resources/Shaders/default.frag"));

    camera = new Camera();

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



    std::shared_ptr<MeshRenderer> teapotGameObject = std::make_shared<MeshRenderer>(teapot);
	std::shared_ptr<MeshRenderer> triangleGameObject = std::make_shared<MeshRenderer>(triangle);
	std::shared_ptr<MeshRenderer> quadGameObject = std::make_shared<MeshRenderer>(quad);
	std::shared_ptr<MeshRenderer> circleGameObject = std::make_shared<MeshRenderer>(circle);
	std::shared_ptr<MeshRenderer> cubeGameObject = std::make_shared<MeshRenderer>(cube);
	std::shared_ptr<MeshRenderer> sphereGameObject = std::make_shared<MeshRenderer>(sphere);
	std::shared_ptr<MeshRenderer> icosphereGameObject = std::make_shared<MeshRenderer>(icosphere);
	std::shared_ptr<MeshRenderer> cylinderGameObject = std::make_shared<MeshRenderer>(cylinder);
	std::shared_ptr<MeshRenderer> coneGameObject = std::make_shared<MeshRenderer>(cone);
	std::shared_ptr<MeshRenderer> planeGameObject = std::make_shared<MeshRenderer>(plane);

	addToUpdateList(teapotGameObject);
	addToUpdateList(triangleGameObject);
	addToUpdateList(quadGameObject);
	addToUpdateList(circleGameObject);
	addToUpdateList(cubeGameObject);
	addToUpdateList(sphereGameObject);
	addToUpdateList(icosphereGameObject);
	addToUpdateList(cylinderGameObject);
	addToUpdateList(coneGameObject);
	addToUpdateList(planeGameObject);

	addToRenderList(teapotGameObject);
	addToRenderList(triangleGameObject);
	addToRenderList(quadGameObject);
	addToRenderList(circleGameObject);
	addToRenderList(cubeGameObject);
	addToRenderList(sphereGameObject);
	addToRenderList(icosphereGameObject);
	addToRenderList(cylinderGameObject);
	addToRenderList(coneGameObject);
	addToRenderList(planeGameObject);



	QMatrix4x4 world;
	world.setToIdentity();
	QMatrix4x4 proj = camera->getProjectionMatrix();
	QVector2D texScale(1.0f, 1.0f);

	//mDefaultShader->setUniformValue("mWorld", world);
	//mDefaultShader->setUniformValue("mProj", proj);
	//mDefaultShader->setUniformValue("mTexScale", texScale);
	//mDefaultShader->setUniformValue("mUseTexture", false);
	//mDefaultShader->setUniformValue("mUseColor", true);
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
}

void TestScene::update(float deltaTime)
{
}

void TestScene::render()
{

}
