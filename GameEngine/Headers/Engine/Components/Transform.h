#pragma once

#include <qvector3d.h>
#include <qquaternion.h>
#include <qmatrix4x4.h>
#include <vector>

#include "Engine/Scenes/GameObject.h"
#include "Engine/Scenes/Component.h"

class Transform : public Component
{
public:
	Transform(GameObject* gameObject);
	virtual ~Transform();

	void position(const QVector3D& position);
	void rotate(const QQuaternion& rotation);
	void scale(const QVector3D& scale);

	void setWorldPosition(const QVector3D& position);
	void setWorldRotation(const QQuaternion& rotation);
	void setWorldScale(const QVector3D& scale);

	void setLocalPosition(const QVector3D& position);
	void setLocalRotation(const QQuaternion& rotation);
	void setLocalScale(const QVector3D& scale);

	void setParent(GameObject* parent);
	GameObject* getParent() const;
	void addChild(GameObject* child);
	void removeChild(GameObject* child);
	int getChildCount() const;
	GameObject* getChild(int index) const;
	int getChildIndex(GameObject* child) const;


	QMatrix4x4 getLocalToWorldMatrix() const;
	QMatrix4x4 getWorldToLocalMatrix() const;

	Transform* clone() override;
public:
	QVector3D worldPosition;
	QQuaternion worldRotation;
	QVector3D worldScale;

	QVector3D localPosition;
	QQuaternion localRotation;
	QVector3D localScale;

	GameObject* parent;
	std::vector<GameObject*> children;
};