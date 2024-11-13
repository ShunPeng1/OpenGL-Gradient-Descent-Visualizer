#include "Qt/Inspector/NodeWidgets/TransformWidget.h"
#include <cmath>

TransformWidget::TransformWidget(Transform* transform, QWidget* parent) : QWidget(parent), mTransform(nullptr), mIsUpdating(false) {
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

	// Connect signals
    connect(mPosX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onPositionSet);
    connect(mPosY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onPositionSet);
    connect(mPosZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onPositionSet);

    connect(mRotX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onRotationSet);
    connect(mRotY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onRotationSet);
    connect(mRotZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onRotationSet);

    connect(mScaleX, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onScaleSet);
    connect(mScaleY, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onScaleSet);
    connect(mScaleZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &TransformWidget::onScaleSet);

    setTransform(transform);
}

TransformWidget::~TransformWidget() {
    clearTransform();
}

void TransformWidget::setTransform(Transform* transform) {
    disconnectSignals();
    
    mTransform = transform;

    updateUI();
    connectSignals();
}

void TransformWidget::clearTransform() {
    disconnectSignals();
    
    mTransform = nullptr;
}

void TransformWidget::onPositionChanged(QVector3D position)
{
    mIsUpdating = true;
	mPosX->setValue(position.x());
	mPosY->setValue(position.y());
	mPosZ->setValue(position.z());
    mIsUpdating = false;
}

void TransformWidget::onRotationChanged(QQuaternion rotation)
{
    mIsUpdating = true;
	QVector3D euler = rotation.toEulerAngles();
	mRotX->setValue(euler.x());
	mRotY->setValue(euler.y());
	mRotZ->setValue(euler.z());
    mIsUpdating = false;
}

void TransformWidget::onScaleChanged(QVector3D scale)
{
    mIsUpdating = true;
	mScaleX->setValue(scale.x());
	mScaleY->setValue(scale.y());
	mScaleZ->setValue(scale.z());
    mIsUpdating = false;
}


void TransformWidget::onPositionSet(double value) {
    if (mIsUpdating) {
        return;
    }

	QVector3D position(mPosX->value(), mPosY->value(), mPosZ->value());
	mTransform->setWorldPosition(position);
}

void TransformWidget::onRotationSet(double value) {
    if (mIsUpdating) {
        return;
    }

    QQuaternion rotation = QQuaternion::fromEulerAngles(mRotX->value(), mRotY->value(), mRotZ->value());
	mTransform->setWorldRotation(rotation);
}

void TransformWidget::onScaleSet(double value) {
    if (mIsUpdating) {
        return;
    }

	QVector3D scale(mScaleX->value(), mScaleY->value(), mScaleZ->value());
	mTransform->setWorldScale(scale);
}

void TransformWidget::updateUI() {
	mIsUpdating = true;
    if (mTransform) {
        QVector3D position = mTransform->getWorldPosition();
        QQuaternion rotation = mTransform->getWorldRotation();
        QVector3D scale = mTransform->getWorldScale();

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
    else {
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
	mIsUpdating = false;
}

void TransformWidget::connectSignals() {
    if (!mTransform){
        return;
    }

	connect(mTransform, &Transform::positionChanged, this, &TransformWidget::onPositionChanged);
	connect(mTransform, &Transform::rotationChanged, this, &TransformWidget::onRotationChanged);
	connect(mTransform, &Transform::scaleChanged, this, &TransformWidget::onScaleChanged);
}

void TransformWidget::disconnectSignals() {
    if (!mTransform) {
        return;
    }

	disconnect(mTransform, &Transform::positionChanged, this, &TransformWidget::onPositionChanged);
	disconnect(mTransform, &Transform::rotationChanged, this, &TransformWidget::onRotationChanged);
	disconnect(mTransform, &Transform::scaleChanged, this, &TransformWidget::onScaleChanged);
}