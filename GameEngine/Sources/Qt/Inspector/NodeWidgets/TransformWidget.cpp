// TransformWidget.cpp
#include "Qt/Inspector/NodeWidgets/TransformWidget.h"
#include <cmath>

TransformWidget::TransformWidget(QWidget* parent) : QWidget(parent), mTransform() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Position
    QHBoxLayout* posLayout = new QHBoxLayout();
    posLayout->addWidget(new QLabel("Position:"));
    mPosX = createDoubleSpinBox(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 1.0, 0.0);
    mPosY = createDoubleSpinBox(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 1.0, 0.0);
    mPosZ = createDoubleSpinBox(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 1.0, 0.0);
    posLayout->addWidget(mPosX);
    posLayout->addWidget(mPosY);
    posLayout->addWidget(mPosZ);
    mainLayout->addLayout(posLayout);

    // Rotation
    QHBoxLayout* rotLayout = new QHBoxLayout();
    rotLayout->addWidget(new QLabel("Rotation:"));
    mRotX = createDoubleSpinBox(-360.0, 360.0, 1.0, 0.0);
    mRotY = createDoubleSpinBox(-360.0, 360.0, 1.0, 0.0);
    mRotZ = createDoubleSpinBox(-360.0, 360.0, 1.0, 0.0);
    rotLayout->addWidget(mRotX);
    rotLayout->addWidget(mRotY);
    rotLayout->addWidget(mRotZ);
    mainLayout->addLayout(rotLayout);

    // Scale
    QHBoxLayout* scaleLayout = new QHBoxLayout();
    scaleLayout->addWidget(new QLabel("Scale:"));
    mScaleX = createDoubleSpinBox(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 0.1, 1.0);
    mScaleY = createDoubleSpinBox(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 0.1, 1.0);
    mScaleZ = createDoubleSpinBox(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), 0.1, 1.0);
    scaleLayout->addWidget(mScaleX);
    scaleLayout->addWidget(mScaleY);
    scaleLayout->addWidget(mScaleZ);
    mainLayout->addLayout(scaleLayout);

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
    if (auto transform = mTransform.lock()) {
        transform->setWorldPosition(getPosition());
    }
    emit transformChanged();
}

void TransformWidget::onRotationChanged() {
	if (auto transform = mTransform.lock()) {
		transform->setWorldRotation(getRotation());
	}
    emit transformChanged();
}

void TransformWidget::onScaleChanged() {
	if (auto transform = mTransform.lock()) {
		transform->setWorldScale(getScale());
	}
    emit transformChanged();
}

QDoubleSpinBox* TransformWidget::createDoubleSpinBox(double min, double max, double step, double value) {
    QDoubleSpinBox* spinBox = new QDoubleSpinBox();
    spinBox->setRange(min, max);
    spinBox->setSingleStep(step);
    spinBox->setValue(value);
    return spinBox;
}