#include "Engine/Components/Material.h"


Material::Material(const QVector3D& mAmbient, const QVector3D& mDiffuse, const QVector3D& mSpecular, float mShininess, float mColorFactor, float mTextureFactor, float mPhongFactor)
    : mAmbient(mAmbient), mDiffuse(mDiffuse), mSpecular(mSpecular), mShininess(mShininess), mColorFactor(mColorFactor), mTextureFactor(mTextureFactor), mPhongFactor(mPhongFactor)
{
}

void Material::setAmbient(const QVector3D& ambient) {
    mAmbient = ambient;
	emit ambientChanged(ambient);
}

void Material::setDiffuse(const QVector3D& diffuse) {
    mDiffuse = diffuse;
	emit diffuseChanged(diffuse);
}

void Material::setSpecular(const QVector3D& specular) {
    mSpecular = specular;
	emit specularChanged(specular);
}

void Material::setShininess(float shininess) {
    mShininess = shininess;
	emit shininessChanged(shininess);
}

void Material::setColorFactor(float colorFactor)
{
	mColorFactor = colorFactor;
	emit colorFactorChanged(colorFactor);
}

void Material::setTextureFactor(float textureFactor)
{
	mTextureFactor = textureFactor;
    emit textureFactorChanged(textureFactor);
}

void Material::setPhongFactor(float phongFactor)
{
	mPhongFactor = phongFactor;
    emit phongFactorChanged(phongFactor);
}

const QVector3D& Material::getAmbient() const {
    return mAmbient;
}

const QVector3D& Material::getDiffuse() const {
    return mDiffuse;
}

const QVector3D& Material::getSpecular() const {
    return mSpecular;
}

 const float Material::getShininess() const {
    return mShininess;
}

const float Material::getColorFactor() const
{
	return mColorFactor;
}

const float Material::getTextureFactor() const
{
    return mTextureFactor;
}

const float Material::getPhongFactor() const
{
    return mPhongFactor;
}

QMatrix3x3 Material::getMaterial() const
{
    QMatrix3x3 material;
    material(0, 0) = mAmbient.x();
    material(1, 0) = mAmbient.y();
    material(2, 0) = mAmbient.z();
    material(0, 1) = mDiffuse.x();
    material(1, 1) = mDiffuse.y();
    material(2, 1) = mDiffuse.z();
    material(0, 2) = mSpecular.x();
    material(1, 2) = mSpecular.y();
    material(2, 2) = mSpecular.z();
    return material;
    
}


