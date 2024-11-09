// TransformWidget.cpp
#include "Qt/Inspector/NodeWidgets/TransformWidget.h"
#include <cmath>

TransformWidget::TransformWidget(std::shared_ptr<Transform> transform, QWidget* parent) : QWidget(parent), mTransform() {
    QVBoxLayout* widgetLayout = new QVBoxLayout(this);

    SectionWidget* section = new SectionWidget("Transform", 0, this);
    mSection = section;
    widgetLayout->addWidget(section);

    QVBoxLayout* mainLayout = new QVBoxLayout(section);

    // Position
    VectorFieldLayout* posLayout = new VectorFieldLayout("Position:", std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 1.0, 0.0, 3, this);
    mPosX = posLayout->getSpinBoxes()[0];
    mPosY = posLayout->getSpinBoxes()[1];
    mPosZ = posLayout->getSpinBoxes()[2];
    mainLayout->addLayout(posLayout);

    // Rotation
    VectorFieldLayout* rotLayout = new VectorFieldLayout("Rotation:", -360.0, 360.0, 1.0, 0.0, 3, this);
    mRotX = rotLayout->getSpinBoxes()[0];
    mRotY = rotLayout->getSpinBoxes()[1];
    mRotZ = rotLayout->getSpinBoxes()[2];
    mainLayout->addLayout(rotLayout);

    // Scale
    VectorFieldLayout* scaleLayout = new VectorFieldLayout("Scale:", std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 0.1, 1.0, 3, this);
    mScaleX = scaleLayout->getSpinBoxes()[0];
    mScaleY = scaleLayout->getSpinBoxes()[1];
    mScaleZ = scaleLayout->getSpinBoxes()[2];
    mainLayout->addLayout(scaleLayout);

    section->setContentLayout(*mainLayout);
    
	// Set the transform
    mTransform = transform;
    if (auto t = mTransform.lock()) {
        QVector3D position = t->getWorldPosition();
        QQuaternion rotation = t->getWorldRotation();
        QVector3D scale = t->getWorldScale();

        mPosX->setValue(position.x());
        mPosY->setValue(position.y());
        mPosZ->setValue(position.z());

        QVector3D euler = rotation.toEulerAngles();
        mRotX->setValue(euler.x());
        mRotY->setValue(euler.y());
        mRotZ->setValue(euler.z());

        mScaleX->setValue(scale.x());
        mScaleY->setValue(scale.y());
        mScaleZ->setValue(scale.z());
    }


	// Connect signals
    connect(mPosX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onPositionChanged);
    connect(mPosY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onPositionChanged);
    connect(mPosZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onPositionChanged);

    connect(mRotX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onRotationChanged);
    connect(mRotY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onRotationChanged);
    connect(mRotZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onRotationChanged);

    connect(mScaleX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onScaleChanged);
    connect(mScaleY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onScaleChanged);
    connect(mScaleZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onScaleChanged);
}

TransformWidget::~TransformWidget()
{

}

void TransformWidget::setTransform(std::shared_ptr<Transform> transform) {
	mTransform = transform;
	mIsUpdating = true;
	if (auto t = mTransform.lock()) {
		QVector3D position = t->getWorldPosition();
		QQuaternion rotation = t->getWorldRotation();
		QVector3D scale = t->getWorldScale();

		mPosX->setValue(position.x());
		mPosY->setValue(position.y());
		mPosZ->setValue(position.z());

		QVector3D euler = rotation.toEulerAngles();
		mRotX->setValue(euler.x());
		mRotY->setValue(euler.y());
		mRotZ->setValue(euler.z());

		mScaleX->setValue(scale.x());
		mScaleY->setValue(scale.y());
		mScaleZ->setValue(scale.z());
	}
	mIsUpdating = false;
}

void TransformWidget::clearTransform()
{
    mTransform.reset();
	mPosX->setValue(0.0);
	mPosY->setValue(0.0);
	mPosZ->setValue(0.0);

	mRotX->setValue(0.0);
	mRotY->setValue(0.0);
	mRotZ->setValue(0.0);

	mScaleX->setValue(1.0);
	mScaleY->setValue(1.0);
	mScaleZ->setValue(1.0);

}


QVector3D TransformWidget::getPosition() const {
    return QVector3D(mPosX->value(), mPosY->value(), mPosZ->value());
}

QQuaternion TransformWidget::getRotation() const {
    return QQuaternion::fromEulerAngles(mRotX->value(), mRotY->value(), mRotZ->value());
}

QVector3D TransformWidget::getScale() const {
    return QVector3D(mScaleX->value(), mScaleY->value(), mScaleZ->value());
}

void TransformWidget::onPositionChanged() {
	if (mIsUpdating) {
		return;
	}
    if (auto transform = mTransform.lock()) {
        transform->setWorldPosition(getPosition());
    }
    emit transformChanged();
}

void TransformWidget::onRotationChanged() {
    if (mIsUpdating) {
        return;
    }
	if (auto transform = mTransform.lock()) {
		transform->setWorldRotation(getRotation());
	}
    emit transformChanged();
}

void TransformWidget::onScaleChanged() {
    if (mIsUpdating) {
        return;
    }
	if (auto transform = mTransform.lock()) {
		transform->setWorldScale(getScale());
	}
    emit transformChanged();
}

