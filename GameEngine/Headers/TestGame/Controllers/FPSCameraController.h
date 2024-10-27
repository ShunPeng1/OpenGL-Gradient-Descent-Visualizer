#ifndef FPS_CAMERA_CONTROLLER_H
#define FPS_CAMERA_CONTROLLER_H


#include "Qt/Inputs/InputSubscriber.h"
#include "Engine/Nodes/Camera.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QElapsedTimer>
#include <QtMath>
#include <QQuaternion>
#include <unordered_map>

class FPSCameraController : public InputSubscriber
{
public:
    FPSCameraController(Camera* camera);

    void updateKeyPress(QKeyEvent* event) override;
	void updateKeyRelease(QKeyEvent* event) override;
    void updateMouseMove(QMouseEvent* event) override;
    void updateResizeGL(int w, int h) override;
    void update(float deltaTime) override;

private:
    Camera* mCamera;

    float mYaw;
    float mPitch;
    bool mFirstMouse;
    float mLastX;
    float mLastY;
    float mSensitivity;
    float mSpeed;

    std::unordered_map<int, bool> mKeyStates;
};


#endif // !FPS_CAMERA_CONTROLLER_H