#include "Engine/Scenes/Scene.h"
#include "Engine/Loaders/ModelLoader.h"
#include "TestGame/Controllers/FPSCameraController.h"
#include "Engine/Nodes/MeshRenderer.h"

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	void load() override;
	void init() override;

private:
	FPSCameraController* mCameraController;


};
