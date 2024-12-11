#pragma once

#include "Engine/Interfaces/IComponent.h"
#include <QVector3D>
#include <QMatrix3x3>
#include <QObject>

class Material : public QObject, public IComponent
{
    Q_OBJECT
public:

    Material(const QVector3D& ambient = QVector3D(1.0f, 1.0f, 1.0f),
        const QVector3D& diffuse = QVector3D(1.0f, 1.0f, 1.0f),
        const QVector3D& specular = QVector3D(1.0f, 1.0f, 1.0f),
		float shininess = 32.0f, float colorFactor = 1.0f, float textureFactor = 0.0f, float phongFactor = 0.0f);

    void setAmbient(const QVector3D& ambient);
    void setDiffuse(const QVector3D& diffuse);
    void setSpecular(const QVector3D& specular);
    void setShininess(float shininess);
	void setColorFactor(float colorFactor);
	void setTextureFactor(float textureFactor);
	void setPhongFactor(float phongFactor);

    const QVector3D& getAmbient() const;
    const QVector3D& getDiffuse() const;
    const QVector3D& getSpecular() const;
	const float getShininess() const;
	const float getColorFactor() const;
	const float getTextureFactor() const;
	const float getPhongFactor() const;

	QMatrix3x3 getMaterial() const;

signals:
	void ambientChanged(const QVector3D& ambient);
	void diffuseChanged(const QVector3D& diffuse);
	void specularChanged(const QVector3D& specular);
	void shininessChanged(float shininess);
	void colorFactorChanged(float colorFactor);
	void textureFactorChanged(float textureFactor);
	void phongFactorChanged(float phongFactor);

private:
    QVector3D mAmbient;
    QVector3D mDiffuse;
    QVector3D mSpecular;

    float mShininess;

	float mColorFactor = 1.0f;
	float mTextureFactor = 0.0f;
	float mPhongFactor = 0.0f;

};