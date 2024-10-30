#pragma once

#include "Engine/Nodes/Container.h"
#include <QOpenGLExtraFunctions>

class Camera : public Container, public QOpenGLExtraFunctions
{
public:
	Camera();
	virtual ~Camera() noexcept;

	
	void setFov(float fov);
	void setNear(float near);
	void setFar(float far);
	void setAspectRatio(float width, float height);
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

protected: 
	virtual void init(Scene* scene) override;
	virtual void update(float deltaTime) override;
	virtual void render(ShaderProgram& shaderProgram) override;

protected:
	float mFov;
	float mNear;
	float mFar;
	float mAspectRatio;
	float mWidth;
	float mIsOrtho;
	bool mDirty;
};