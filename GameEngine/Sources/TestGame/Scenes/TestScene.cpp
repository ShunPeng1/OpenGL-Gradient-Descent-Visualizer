#include "Engine/Engine.h"
#include "Engine/Scenes/Scene.h"
#include "Engine/GameObjects/Camera.h"




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

};

TestScene::TestScene()
{

}

TestScene::~TestScene()
{
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
