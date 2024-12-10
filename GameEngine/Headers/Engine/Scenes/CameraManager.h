#pragma once

#include "Engine/Engine.h"
#include "Engine/Renders/ShaderProgram.h"
#include "Engine/Nodes/Camera.h"
#include "vector"

class CameraManager {

public:
	CameraManager();
	~CameraManager();

	void addCamera(Camera* camera);
	void removeCamera(Camera* camera);

	void setMainCamera(Camera* camera);
	Camera* getMainCamera() const;

	std::vector<Camera*> getCameras() const;

	void setShowGizmos(bool showGizmos);

	void renderWithMainCamera(ShaderProgram& shaderProgram);

private:
	std::vector<Camera*> mCameras;
	Camera* mMainCamera;

	bool mShowGizmos;
};