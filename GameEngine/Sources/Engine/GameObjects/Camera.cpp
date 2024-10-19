#include "Engine/GameObjects/Camera.h"

Camera::Camera()
{
	mFov = 45.0f;
	mNear = 0.1f;
	mFar = 1000.0f;
	mAspectRatio = 16.0f/9.0f;
	mIsOrtho = false;
}

Camera::~Camera() noexcept
{
}

void Camera::update(float deltaTime)
{

}

void Camera::setFov(float fov)
{
	mFov = fov;
}

void Camera::setNear(float near)
{
	mNear = near;
}

void Camera::setFar(float far)
{
	mFar = far;
}

void Camera::setAspectRatio(float aspectRatio)
{
	mAspectRatio = aspectRatio;
}

void Camera::setIsOrtho(bool isOrtho)
{
	mIsOrtho = isOrtho;
}

float Camera::getFov() const
{
	return 0.0f;
}

float Camera::getNear() const
{
	return 0.0f;
}

float Camera::getFar() const
{
	return 0.0f;
}

float Camera::getAspectRatio() const
{
	return 0.0f;
}

bool Camera::getIsOrtho() const
{
	return mIsOrtho;
}

QMatrix4x4 Camera::getViewMatrix()
{
	QMatrix4x4 view;
	QVector3D mPosition = transform.getWorldPosition();
	QVector3D mFront = transform.getWorldRotation() * QVector3D(0.0f, 0.0f, -1.0f);
	QVector3D mUp = transform.getWorldRotation() * QVector3D(0.0f, 1.0f, 0.0f);

	view.lookAt(mPosition, mPosition + mFront, mUp);
	return view;
}
