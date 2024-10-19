#pragma once

#include "Engine/GameObjects/Container.h"
#include <QOpenGLExtraFunctions>

class Camera : public Container , public QOpenGLExtraFunctions
{
public:
	Camera();
	virtual ~Camera() noexcept;

	virtual void update(float deltaTime) override;

	void setFov(float fov);
	void setNear(float near);
	void setFar(float far);
	void setAspectRatio(float aspectRatio);
	void setIsOrtho(bool isOrtho);

	float getFov() const;
	float getNear() const;
	float getFar() const;
	float getAspectRatio() const;
	bool getIsOrtho() const;

	QMatrix4x4 getViewMatrix();

private:
	float mFov;
	float mNear;
	float mFar;
	float mAspectRatio;
	float mIsOrtho;
};