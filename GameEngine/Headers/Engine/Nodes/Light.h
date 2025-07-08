#pragma once

#include "Engine/Nodes/Container.h"
#include <QVector3D>
#include <QMatrix3x3>

class Light : public Container
{
	Q_OBJECT

protected:
	virtual void render(ShaderProgram& shaderProgram) override;

public:

	void setAmbientIntensity(const QVector3D& intensity);
	QVector3D getAmbientIntensity() const;

	void setDiffuseIntensity(const QVector3D& intensity);
	QVector3D getDiffuseIntensity() const;

	void setSpecularIntensity(const QVector3D& intensity);
	QVector3D getSpecularIntensity() const;


	QMatrix3x3 getLightIntensity() const;

signals:
	void ambientIntensityChanged(const QVector3D& intensity);
	void diffuseIntensityChanged(const QVector3D& intensity);
	void specularIntensityChanged(const QVector3D& intensity);


private:
	QVector3D mAmbientIntensity;
	QVector3D mDiffuseIntensity;
	QVector3D mSpecularIntensity;

public: // Interfaces
	virtual void write(QJsonObject& json) const override;
	virtual void read(const QJsonObject& json) override;
	virtual void* accept(INodeVisitor* visitor) override;
};


