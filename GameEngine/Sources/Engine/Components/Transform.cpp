#include "Engine/Components/Transform.h"


Transform::Transform(GameObject* gameObject) : Component(gameObject)
{
	worldPosition = QVector3D(0.0f, 0.0f, 0.0f);
	worldRotation = QQuaternion(1.0f, 0.0f, 0.0f, 0.0f);
	worldScale = QVector3D(1.0f, 1.0f, 1.0f);

	localPosition = QVector3D(0.0f, 0.0f, 0.0f);
	localRotation = QQuaternion(1.0f, 0.0f, 0.0f, 0.0f);
	localScale = QVector3D(1.0f, 1.0f, 1.0f);

	parent = nullptr;
	children = std::vector<GameObject*>();

}

Transform::~Transform()
{
}

void Transform::position(const QVector3D& position)
{
}

void Transform::rotate(const QQuaternion& rotation)
{
}

void Transform::scale(const QVector3D& scale)
{
}

void Transform::setWorldPosition(const QVector3D& position)
{
}

void Transform::setWorldRotation(const QQuaternion& rotation)
{
}

void Transform::setWorldScale(const QVector3D& scale)
{
}

void Transform::setLocalPosition(const QVector3D& position)
{
}

void Transform::setLocalRotation(const QQuaternion& rotation)
{
}

void Transform::setLocalScale(const QVector3D& scale)
{
}

void Transform::setParent(GameObject* parent)
{
}

GameObject* Transform::getParent() const
{
	return nullptr;
}

void Transform::addChild(GameObject* child)
{
}

void Transform::removeChild(GameObject* child)
{
}

int Transform::getChildCount() const
{
	return 0;
}

GameObject* Transform::getChild(int index) const
{
	return nullptr;
}

int Transform::getChildIndex(GameObject* child) const
{
	return 0;
}

QMatrix4x4 Transform::getLocalToWorldMatrix() const
{
	return QMatrix4x4();
}

QMatrix4x4 Transform::getWorldToLocalMatrix() const
{
	return QMatrix4x4();
}

Transform* Transform::clone()
{
	return nullptr;
}
