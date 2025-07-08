#pragma once

#include "Engine/Nodes/Container.h"
#include <QOpenGLExtraFunctions>
#include "Engine/Renders/Vertex.h"

class Camera : public Container, public QOpenGLExtraFunctions
{
	Q_OBJECT

public:
	Camera();
	virtual ~Camera() noexcept;

	void drawFrustum(ShaderProgram& shaderProgram);

	QVector<QVector3D> calculateFrustumCorners();

	void setFov(float fov);
	void setNear(float near);
	void setFar(float far);
	void setAspectRatio(float width, float height);
	void setAspectRatio(float aspectRatio);
	void setIsOrtho(bool isOrtho);
	void setWidth(float width);
	void setDrawFrustum(bool drawFrustum);

	float getFov() const;
	float getNear() const;
	float getFar() const;
	float getAspectRatio() const;
	bool getIsOrtho() const;
	float getWidth() const;
	float getHeight() const;
	bool getDrawFrustum() const;

	QMatrix4x4 getViewMatrix();
	QMatrix4x4 getProjectionMatrix();

public: // Interfaces
	virtual void write(QJsonObject& json) const override;
	virtual void read(const QJsonObject& json) override;
	virtual void* accept(INodeVisitor* visitor) override;

signals:
	void fovChanged(float);
	void nearChanged(float);
	void farChanged(float);
	void aspectRatioChanged(float);
	void isOrthoChanged(bool);
	void widthChanged(float);
	void drawFrustumChanged(bool);

protected:
	virtual void init() override;
	virtual void start(IScene* scene) override;
	virtual void update(float deltaTime) override;
	virtual void render(ShaderProgram& shaderProgram) override;

protected:
	float mFov;
	float mNear;
	float mFar;
	float mAspectRatio;
	float mWidth;
	float mHeight;
	float mIsOrtho;
	bool mDirty;
	bool mDrawFrustum;

	QMatrix4x4 mProjection;

	unsigned int mVAO;
	unsigned int mVBO;
};