#ifndef TRANSFORM_H
#define TRANSFORM_H


#include <qvector3d.h>
#include <qquaternion.h>
#include <qmatrix4x4.h>
#include <vector>
#include <memory> 

#include "Engine/Interfaces/IComponent.h"
#include <QObject>

class Transform : public QObject, public IComponent
{
	Q_OBJECT

public:
	Transform();
	virtual ~Transform();

	void position(const QVector3D& position);
	void rotate(const QQuaternion& rotation);
	void scale(const QVector3D& scale);

	void setWorldPosition(const QVector3D& position);
	void setWorldRotation(const QQuaternion& rotation);
	void setWorldScale(const QVector3D& scale);

	QVector3D getWorldPosition();
	QQuaternion getWorldRotation();
	QVector3D getWorldScale();

	void setLocalPosition(const QVector3D& position);
	void setLocalRotation(const QQuaternion& rotation);
	void setLocalScale(const QVector3D& scale);

	QVector3D getLocalPosition();
	QQuaternion getLocalRotation();
	QVector3D getLocalScale();

	void setParent(Transform* parent);
	Transform* getParent() const;
	int getChildCount() const;
	Transform* getChild(int index) const;
	int getChildIndex(Transform* child) const;


	QMatrix4x4 getWorldMatrix();
	QMatrix4x4 getLocalMatrix();


signals:
	void positionChanged(QVector3D);

signals:
	void rotationChanged(QQuaternion);

signals:
	void scaleChanged(QVector3D);

private:

	void addChild(Transform* child);
	void removeChild(Transform* child);
	void updateChildrenWorldMatrix();

	QVector3D mWorldPosition;
	QQuaternion mWorldRotation;
	QVector3D mWorldScale;

	Transform* mParent;
	std::vector<Transform*> mChildren; // Use unique_ptr for children

};



#endif // !TRANSFORM_H