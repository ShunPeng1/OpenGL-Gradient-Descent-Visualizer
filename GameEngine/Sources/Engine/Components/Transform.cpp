#include "Engine/Components/Transform.h"


Transform::Transform() : mParent(nullptr)
{
	mLocalPosition = QVector3D(0.0f, 0.0f, 0.0f);
	mLocalRotation = QQuaternion(1.0f, 0.0f, 0.0f, 0.0f);
	mLocalScale = QVector3D(1.0f, 1.0f, 1.0f);

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
	if (mParent)
	{
		QMatrix4x4 parentInverse = mParent->getWorldMatrix().inverted();
		mLocalPosition = parentInverse.map(position);
	}
	else
	{
		mLocalPosition = position;
	}
	mIsDirty = true;

	emit positionChanged(mLocalPosition);

	updateChildrenWorldMatrix();
}

void Transform::setWorldRotation(const QQuaternion& rotation)
{
	if (mParent)
	{
		QMatrix4x4 parentInverse = mParent->getWorldMatrix().inverted();
		QMatrix4x4 rotationMatrix;
		rotationMatrix.rotate(rotation);
		QMatrix4x4 resultMatrix = parentInverse * rotationMatrix;
		mLocalRotation = QQuaternion::fromRotationMatrix(resultMatrix.toGenericMatrix<3, 3>());
	}
	else
	{
		mLocalRotation = rotation;
	}
	mIsDirty = true;

	emit rotationChanged(mLocalRotation);
	updateChildrenWorldMatrix();
}

void Transform::setWorldScale(const QVector3D& scale)
{
	if (mParent)
	{
		QMatrix4x4 parentInverse = mParent->getWorldMatrix().inverted();
		QMatrix4x4 scaleMatrix;
		scaleMatrix.scale(scale);
		QMatrix4x4 resultMatrix = parentInverse * scaleMatrix;
		mLocalScale = QVector3D(resultMatrix(0, 0), resultMatrix(1, 1), resultMatrix(2, 2));
	}
	else
	{
		mLocalScale = scale;
	}
	mIsDirty = true;

	emit scaleChanged(mLocalScale);
	updateChildrenWorldMatrix();
}

QVector3D Transform::getWorldPosition()
{
	if (mParent)
	{
		return mParent->getWorldMatrix().map(mLocalPosition);
	}
	return mLocalPosition;
}

QQuaternion Transform::getWorldRotation()
{
	if (mParent)
	{
		QMatrix4x4 parentMatrix = mParent->getWorldMatrix();
		QMatrix4x4 rotationMatrix;
		rotationMatrix.rotate(mLocalRotation);
		QMatrix4x4 resultMatrix = parentMatrix * rotationMatrix;
		return QQuaternion::fromRotationMatrix(resultMatrix.toGenericMatrix<3, 3>());
	}
	return mLocalRotation;
}

QVector3D Transform::getWorldScale()
{
	if (mParent)
	{
		QMatrix4x4 parentMatrix = mParent->getWorldMatrix();
		QMatrix4x4 scaleMatrix;
		scaleMatrix.scale(mLocalScale);
		QMatrix4x4 resultMatrix = parentMatrix * scaleMatrix;
		return QVector3D(resultMatrix(0, 0), resultMatrix(1, 1), resultMatrix(2, 2));
	}
	return mLocalScale;
}

void Transform::setLocalPosition(const QVector3D& position)
{
	mLocalPosition = position;
	mIsDirty = true;

	emit positionChanged(mLocalPosition);
	updateChildrenWorldMatrix();
}

void Transform::setLocalRotation(const QQuaternion& rotation)
{
	mLocalRotation = rotation;
	mIsDirty = true;

	emit rotationChanged(mLocalRotation);
	updateChildrenWorldMatrix();
}

void Transform::setLocalScale(const QVector3D& scale)
{
	mLocalScale = scale;
	mIsDirty = true;

	emit scaleChanged(mLocalScale);
	updateChildrenWorldMatrix();
}

QVector3D Transform::getLocalPosition()
{
	return mLocalPosition;
}

QQuaternion Transform::getLocalRotation()
{
	return mLocalRotation;
}

QVector3D Transform::getLocalScale()
{
	return mLocalScale;
}

bool Transform::getIsDirty() const
{
	return mIsDirty;
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
	if (child == nullptr)
	{
		return;
	}

	mChildren.push_back(child);
}

void Transform::removeChild(Transform* child)
{
	auto it = std::remove_if(mChildren.begin(), mChildren.end(),
		[child](const Transform* ptr) {
			return ptr == child;
		});
	if (it != mChildren.end())
	{
		(*it)->setParent(nullptr);
		mChildren.erase(it, mChildren.end());
	}
}

int Transform::getChildCount() const
{
	return static_cast<int>(mChildren.size());
}

Transform* Transform::getChild(int index) const
{
	if (index < 0 || index >= static_cast<int>(mChildren.size()))
	{
		return nullptr;
	}
	return mChildren[index];
}

int Transform::getChildIndex(Transform* child) const
{
	for (size_t i = 0; i < mChildren.size(); ++i)
	{
		if (mChildren[i] == child)
		{
			return static_cast<int>(i);
		}
	}
	return -1;
}

QMatrix4x4 Transform::getWorldMatrix()
{
	if (!mIsDirty)
	{
		return mWorldMatrix;
	}
	mIsDirty = false;

	QMatrix4x4 matrix;
	matrix.translate(mLocalPosition);
	matrix.rotate(mLocalRotation);
	matrix.scale(mLocalScale);
	if (mParent)
	{
		mWorldMatrix = mParent->getWorldMatrix() * matrix;
	}
	else
	{
		mWorldMatrix = matrix;
	}
	return mWorldMatrix;
}

QMatrix4x4 Transform::getLocalMatrix()
{
	QMatrix4x4 matrix;
	matrix.translate(mLocalPosition);
	matrix.rotate(mLocalRotation);
	matrix.scale(mLocalScale);
	return matrix;
}

void Transform::computeModelMatrix()
{
	mWorldMatrix = getLocalMatrix();
	mIsDirty = false;
}

void Transform::computeModelMatrix(QMatrix4x4 parentGlobalModelMatrix)
{
	mWorldMatrix = parentGlobalModelMatrix * getLocalMatrix();
	mIsDirty = false;
}

void Transform::updateChildrenWorldMatrix()
{
	if (mParent)
		computeModelMatrix(mParent->getWorldMatrix());
	else
		computeModelMatrix();

	for (const auto& child : mChildren)
	{
		child->updateChildrenWorldMatrix();
	}
}

