#ifndef FPS_CAMERA_CONTROLLER_H
#define FPS_CAMERA_CONTROLLER_H



#include "Engine/GameObjects/Camera.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QElapsedTimer>
#include <QtMath>
#include <QQuaternion>
#include <unordered_map>

class FPSCameraController
{
public:
    FPSCameraController(Camera* camera);
    void handleKeyPress(QKeyEvent* event);
    void handleKeyRelease(QKeyEvent* event);
    void handleMouseMove(QMouseEvent* event);
    void update(float deltaTime);

private:
    Camera* mCamera;
    std::unordered_map<int, bool> mKeyStates;
    float mYaw;
    float mPitch;
    bool mFirstMouse;
    float mLastX;
    float mLastY;
    float mSensitivity;
    float mSpeed;
};


#endif // !FPS_CAMERA_CONTROLLER_H