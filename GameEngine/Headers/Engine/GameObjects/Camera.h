#pragma once

#include "Engine/GameObjects/Container.h"
#include <QOpenGLExtraFunctions>

class Camera : public Container, public QOpenGLExtraFunctions
{
public:
	Camera();
	virtual ~Camera() noexcept;

	virtual void init(Scene *scene) override;
	virtual void update(float deltaTime) override;
	virtual void render(ShaderProgram& shaderProgram) override;

	void setFov(float fov);
	void setNear(float near);
	void setFar(float far);
	void setAspectRatio(float aspectRatio);
	void setIsOrtho(bool isOrtho);
	void setWidth(float width);

	float getFov() const;
	float getNear() const;
	float getFar() const;
	float getAspectRatio() const;
	bool getIsOrtho() const;
	float getWidth() const;

	QMatrix4x4 getViewMatrix();
	QMatrix4x4 getProjectionMatrix();

private:
	float mFov;
	float mNear;
	float mFar;
	float mAspectRatio;
	float mWidth;
	float mIsOrtho;
	bool mDirty;
};