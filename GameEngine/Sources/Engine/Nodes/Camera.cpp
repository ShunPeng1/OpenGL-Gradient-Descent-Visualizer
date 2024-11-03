#include "Engine/Nodes/Camera.h"

Camera::Camera()
{
	mFov = 45.0f;
	mNear = 0.1f;
	mFar = 1000.0f;
	mAspectRatio = 16.0f/9.0f;
	mIsOrtho = false;

	setName("Camera");
}

Camera::~Camera() noexcept
{
}

void Camera::init()
{
	initializeOpenGLFunctions();
}

void Camera::start(Scene* scene)
{

	glEnable(GL_DEPTH_TEST);
}

void Camera::update(float deltaTime)
{

}

void Camera::render(ShaderProgram& shaderProgram)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	QMatrix4x4 view = getViewMatrix();

	shaderProgram.setUniformValue("mView", view);

	if (mDirty) {
		mDirty = false;
		QMatrix4x4 proj = getProjectionMatrix();
		shaderProgram.setUniformValue("mProj", proj);
	}

}

void Camera::setFov(float fov)
{
	mFov = fov;
	mDirty = true;
}

void Camera::setNear(float near)
{
	mNear = near;
	mDirty = true;
}

void Camera::setFar(float far)
{
	mFar = far;
	mDirty = true;
}

void Camera::setAspectRatio(float width, float height)
{
	mAspectRatio = width / height;
	mDirty = true;
}

void Camera::setIsOrtho(bool isOrtho)
{
	mIsOrtho = isOrtho;
	mDirty = true;
}

void Camera::setWidth(float width)
{
	mWidth = width;
	mDirty = true;
}

float Camera::getFov() const
{
	return mFov;
}

float Camera::getNear() const
{
	return mNear;
}

float Camera::getFar() const
{
	return mFar;
}

float Camera::getAspectRatio() const
{
	return mAspectRatio;
}

bool Camera::getIsOrtho() const
{
	return mIsOrtho;
}

float Camera::getWidth() const
{
	return mWidth;
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

QMatrix4x4 Camera::getProjectionMatrix()
{
	QMatrix4x4 projection;

	if (mIsOrtho) {
		// Create an orthographic projection matrix
		float orthoWidth = mWidth; // Define the width of the orthographic view
		float orthoHeight = orthoWidth / mAspectRatio;
		projection.ortho(-orthoWidth / 2, orthoWidth / 2, -orthoHeight / 2, orthoHeight / 2, mNear, mFar);
	}
	else {
		// Create a perspective projection matrix
		projection.perspective(mFov, mAspectRatio, mNear, mFar);
	}

	return projection;
}