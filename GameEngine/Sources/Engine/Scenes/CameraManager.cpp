#include "Engine/Scenes/CameraManager.h"



CameraManager::CameraManager() : mMainCamera(nullptr), mShowGizmos(false) {}

CameraManager::~CameraManager() {
}

void CameraManager::addCamera(Camera* camera) {
    mCameras.push_back(camera);
}

void CameraManager::removeCamera(Camera* camera) {
    auto it = std::remove(mCameras.begin(), mCameras.end(), camera);
    if (it != mCameras.end()) {
        mCameras.erase(it);
    }
}

void CameraManager::setMainCamera(Camera* camera) {
    mMainCamera = camera;
}

Camera* CameraManager::getMainCamera() const {
    return mMainCamera;
}

std::vector<Camera*> CameraManager::getCameras() const {
    return mCameras;
}

void CameraManager::setShowGizmos(bool showGizmos) {
    mShowGizmos = showGizmos;
}

void CameraManager::renderWithMainCamera(ShaderProgram& shaderProgram)
{

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LESS);

	QMatrix4x4 view = mMainCamera->getViewMatrix();
	shaderProgram.setUniformValue("mView", view);
	QMatrix4x4 proj = mMainCamera->getProjectionMatrix();
	shaderProgram.setUniformValue("mProj", proj);

}
