#include "Engine/Nodes/Transform.h"


Transform::Transform() : mParent(nullptr)
{
	mWorldPosition = QVector3D(0.0f, 0.0f, 0.0f);
	mWorldRotation = QQuaternion(1.0f, 0.0f, 0.0f, 0.0f);
	mWorldScale = QVector3D(1.0f, 1.0f, 1.0f);

	mChildren = std::vector<Transform*>();
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
	mWorldPosition = position;
	updateChildrenWorldMatrix();
}

void Transform::setWorldRotation(const QQuaternion& rotation)
{
	mWorldRotation = rotation;
	updateChildrenWorldMatrix();
}

void Transform::setWorldScale(const QVector3D& scale)
{
	mWorldScale = scale;
	updateChildrenWorldMatrix();
}

QVector3D Transform::getWorldPosition()
{
	return mWorldPosition;
}

QQuaternion Transform::getWorldRotation()
{
	return mWorldRotation;
}

QVector3D Transform::getWorldScale()
{
	return mWorldScale;
}

void Transform::setLocalPosition(const QVector3D& position)
{
    if (mParent)
    {
        QMatrix4x4 parentInverse = mParent->getWorldMatrix().inverted();
        QMatrix4x4 translationMatrix;
        translationMatrix.translate(position);
		mWorldPosition = parentInverse.map(translationMatrix.map(QVector3D(0.0f, 0.0f, 0.0f)));
    }
    else
    {
        mWorldPosition = position;
    }
	updateChildrenWorldMatrix();
}

void Transform::setLocalRotation(const QQuaternion& rotation)  
{  
   if (mParent)  
   {  
       QMatrix4x4 parentInverse = mParent->getWorldMatrix().inverted();  
       QMatrix4x4 rotationMatrix;  
       rotationMatrix.rotate(rotation);  
       QMatrix4x4 resultMatrix = parentInverse * rotationMatrix;  
       mWorldRotation = QQuaternion::fromRotationMatrix(resultMatrix.toGenericMatrix<3, 3>());  
   }  
   else  
   {  
       mWorldRotation = rotation;  
   }  
   updateChildrenWorldMatrix();  
}

void Transform::setLocalScale(const QVector3D& scale)
{
	if (mParent)
	{
		QMatrix4x4 parentInverse = mParent->getWorldMatrix().inverted();
		QMatrix4x4 scaleMatrix;
		scaleMatrix.scale(scale);
		QMatrix4x4 resultMatrix = parentInverse * scaleMatrix;
		mWorldScale = resultMatrix.map(QVector3D(1.0f, 1.0f, 1.0f));
	}
	else
	{
		mWorldScale = scale;
	}
	updateChildrenWorldMatrix();
}

QVector3D Transform::getLocalPosition()
{
	if (mParent)
	{
		QMatrix4x4 parentMatrix = mParent->getWorldMatrix();
		QMatrix4x4 parentInverse = parentMatrix.inverted();
		QVector3D result = parentInverse.map(QVector3D(0.0f, 0.0f, 0.0f));
		return result;
	}
	return mWorldPosition;
}

QQuaternion Transform::getLocalRotation()
{
	if (mParent)
	{
		QMatrix4x4 parentMatrix = mParent->getWorldMatrix();
		QMatrix4x4 parentInverse = parentMatrix.inverted();
		QMatrix4x4 rotationMatrix = parentInverse * getWorldMatrix();
		return QQuaternion::fromRotationMatrix(rotationMatrix.toGenericMatrix<3, 3>());
	}
	return mWorldRotation;
}

QVector3D Transform::getLocalScale()
{
	if (mParent)
	{
		QMatrix4x4 parentMatrix = mParent->getWorldMatrix();
		QMatrix4x4 parentInverse = parentMatrix.inverted();
		QVector3D result = parentInverse.map(QVector3D(1.0f, 1.0f, 1.0f));
		return result;
	}
	return mWorldScale;
}

void Transform::setParent(Transform* parent)
{
	if (mParent)
	{
		mParent->removeChild(this);
	}

	mParent = parent;

	if (mParent)
	{
		mParent->addChild(this);
	}
}

Transform* Transform::getParent() const
{
	return mParent;
}

void Transform::addChild(Transform* child)
{
	mChildren.push_back(child);
}

void Transform::removeChild(Transform* child)
{
	int index = getChildIndex(child);
	if (index != -1)
	{
		mChildren.erase(mChildren.begin() + index);
	}
}

int Transform::getChildCount() const
{
	return mChildren.size();
}

Transform* Transform::getChild(int index) const
{
	if (index >= 0 && index < mChildren.size())
	{
		return mChildren[index];
	}
	return nullptr;
}

int Transform::getChildIndex(Transform* child) const
{
	for (int i = 0; i < mChildren.size(); i++)
	{
		if (mChildren[i] == child)
		{
			return i;
		}
	}
	return -1;
}

QMatrix4x4 Transform::getWorldMatrix()
{
    QMatrix4x4 matrix;
    matrix.translate(mWorldPosition);
    matrix.rotate(mWorldRotation);
    matrix.scale(mWorldScale);
    return matrix;
}

QMatrix4x4 Transform::getLocalMatrix()
{
	Transform* parent = getParent();
	QMatrix4x4 matrix;
	if (parent)
	{
		return parent->getWorldMatrix().inverted() * getWorldMatrix();
	}
	else
	{
		return getWorldMatrix();
	}
}


void Transform::updateChildrenWorldMatrix()
{
	for (Transform* child : mChildren)
	{
		child->setWorldPosition(child->getLocalPosition());
		child->setWorldRotation(child->getLocalRotation());
		child->setWorldScale(child->getLocalScale());
	}

}
