#include "Engine/Nodes/Light.h"


QVector3D Light::getAmbientIntensity() const {
	return mAmbientIntensity;
}

QVector3D Light::getDiffuseIntensity() const {
	return mDiffuseIntensity;
}

QVector3D Light::getSpecularIntensity() const {
	return mSpecularIntensity;
}

void Light::setAmbientIntensity(const QVector3D& intensity) {
	mAmbientIntensity = intensity;
}

void Light::setDiffuseIntensity(const QVector3D& intensity) {
	mDiffuseIntensity = intensity;
}

void Light::setSpecularIntensity(const QVector3D& intensity) {
	mSpecularIntensity = intensity;
}

QMatrix3x3 Light::getLightIntensity() const {
	QMatrix3x3 lightIntensity;
	lightIntensity(0, 0) = mAmbientIntensity.x();
	lightIntensity(1, 0) = mAmbientIntensity.y();
	lightIntensity(2, 0) = mAmbientIntensity.z();
	lightIntensity(0, 1) = mDiffuseIntensity.x();
	lightIntensity(1, 1) = mDiffuseIntensity.y();
	lightIntensity(2, 1) = mDiffuseIntensity.z();
	lightIntensity(0, 2) = mSpecularIntensity.x();
	lightIntensity(1, 2) = mSpecularIntensity.y();
	lightIntensity(2, 2) = mSpecularIntensity.z();

	return lightIntensity;
}


void Light::render(ShaderProgram& shaderProgram)
{
	shaderProgram.setUniformValue("mLightIntensity", getLightIntensity());
}

void Light::write(QJsonObject& json) const {
	// Implementation of write method
}

void Light::read(const QJsonObject& json) {
	// Implementation of read method
}

void* Light::accept(INodeVisitor* visitor) {
	// Implementation of accept method
	return nullptr;
}