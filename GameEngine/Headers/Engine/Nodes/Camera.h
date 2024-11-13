#pragma once

#include "Engine/Nodes/Container.h"
#include <QOpenGLExtraFunctions>

class Camera : public Container, public QOpenGLExtraFunctions
{
	Q_OBJECT

public:
	Camera();
	virtual ~Camera() noexcept;

	virtual void init() override;

	void setFov(float fov);
	void setNear(float near);
	void setFar(float far);
	void setAspectRatio(float width, float height);
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

public: // Interfaces
	virtual void write(QJsonObject& json) const override;
	virtual void read(const QJsonObject& json) override;
	virtual void* accept(INodeVisitor* visitor) override;

signals:
	void fovChanged(float);
signals:
	void nearChanged(float);
signals:
	void farChanged(float);
signals:
	void aspectRatioChanged(float);
signals:
	void isOrthoChanged(bool);
signals:
	void widthChanged(float);

protected: 
	virtual void start(IScene* scene) override;
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