#include "TestGame/Controllers/FPSCameraController.h"


FPSCameraController::FPSCameraController(Camera* camera)
    : mCamera(camera), mYaw(-90.0f), mPitch(0.0f), mFirstMouse(true), mLastX(0.0f), mLastY(0.0f), mSensitivity(0.1f), mSpeed(2.5f)
{
	mKeyStates = std::unordered_map<int, bool>();
	mKeyStates[Qt::Key_W] = false;
	mKeyStates[Qt::Key_S] = false;
	mKeyStates[Qt::Key_A] = false;
	mKeyStates[Qt::Key_D] = false;
	mKeyStates[Qt::Key_Q] = false;
	mKeyStates[Qt::Key_E] = false;
}

void FPSCameraController::handleKeyPress(QKeyEvent* event)
{
    mKeyStates[event->key()] = true;
}

void FPSCameraController::handleKeyRelease(QKeyEvent* event)
{
    mKeyStates[event->key()] = false;
}

void FPSCameraController::handleMouseMove(QMouseEvent* event)
{
    if (mFirstMouse) {
        mLastX = event->position().x();
        mLastY = event->position().y();
        mFirstMouse = false;
    }

    float xoffset = mLastX - event->position().x();
    float yoffset = mLastY - event->position().y();
    mLastX = event->position().x();
    mLastY = event->position().y();

    xoffset *= mSensitivity;
    yoffset *= mSensitivity;

    mYaw += xoffset;
    mPitch += yoffset;

    if (mPitch > 89.0f)
        mPitch = 89.0f;
    if (mPitch < -89.0f)
        mPitch = -89.0f;

    QQuaternion yawRotation = QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 1.0f, 0.0f), mYaw);
    QQuaternion pitchRotation = QQuaternion::fromAxisAndAngle(QVector3D(1.0f, 0.0f, 0.0f), mPitch);
    QQuaternion orientation = yawRotation * pitchRotation;

    mCamera->transform.setLocalRotation(orientation);
}

void FPSCameraController::update(float deltaTime)
{
    float cameraSpeed = mSpeed * deltaTime;
    QVector3D position = mCamera->transform.getLocalPosition();
	QQuaternion orientation = mCamera->transform.getLocalRotation();
	QVector3D front = orientation.rotatedVector(QVector3D(0.0f, 0.0f, -1.0f));
	QVector3D up = orientation.rotatedVector(QVector3D(0.0f, 1.0f, 0.0f));

    if (mKeyStates[Qt::Key_W])
        position += cameraSpeed * front;
    if (mKeyStates[Qt::Key_S])
        position -= cameraSpeed * front;
    if (mKeyStates[Qt::Key_A])
        position -= QVector3D::crossProduct(front, up).normalized() * cameraSpeed;
    if (mKeyStates[Qt::Key_D])
        position += QVector3D::crossProduct(front, up).normalized() * cameraSpeed;
    if (mKeyStates[Qt::Key_Q])
        position -= cameraSpeed * up;
    if (mKeyStates[Qt::Key_E])
        position += cameraSpeed * up;

    mCamera->transform.setLocalPosition(position);
}