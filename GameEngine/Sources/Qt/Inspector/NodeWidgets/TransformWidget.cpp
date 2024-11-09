// TransformWidget.cpp
#include "Qt/Inspector/NodeWidgets/TransformWidget.h"
#include <cmath>

TransformWidget::TransformWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Position
    QHBoxLayout* posLayout = new QHBoxLayout();
    posLayout->addWidget(new QLabel("Position:"));
    mPosX = createDoubleSpinBox(-1000.0, 1000.0, 0.1, 0.0);
    mPosY = createDoubleSpinBox(-1000.0, 1000.0, 0.1, 0.0);
    mPosZ = createDoubleSpinBox(-1000.0, 1000.0, 0.1, 0.0);
    posLayout->addWidget(mPosX);
    posLayout->addWidget(mPosY);
    posLayout->addWidget(mPosZ);
    mainLayout->addLayout(posLayout);

    // Rotation
    QHBoxLayout* rotLayout = new QHBoxLayout();
    rotLayout->addWidget(new QLabel("Rotation (Euler):"));
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
    mScaleX = createDoubleSpinBox(0.0, 1000.0, 0.1, 1.0);
    mScaleY = createDoubleSpinBox(0.0, 1000.0, 0.1, 1.0);
    mScaleZ = createDoubleSpinBox(0.0, 1000.0, 0.1, 1.0);
    scaleLayout->addWidget(mScaleX);
    scaleLayout->addWidget(mScaleY);
    scaleLayout->addWidget(mScaleZ);
    mainLayout->addLayout(scaleLayout);

    connect(mPosX, SIGNAL(valueChanged(double)), this, SLOT(onPositionChanged()));
    connect(mPosY, SIGNAL(valueChanged(double)), this, SLOT(onPositionChanged()));
    connect(mPosZ, SIGNAL(valueChanged(double)), this, SLOT(onPositionChanged()));

    connect(mRotX, SIGNAL(valueChanged(double)), this, SLOT(onRotationChanged()));
    connect(mRotY, SIGNAL(valueChanged(double)), this, SLOT(onRotationChanged()));
    connect(mRotZ, SIGNAL(valueChanged(double)), this, SLOT(onRotationChanged()));

    connect(mScaleX, SIGNAL(valueChanged(double)), this, SLOT(onScaleChanged()));
    connect(mScaleY, SIGNAL(valueChanged(double)), this, SLOT(onScaleChanged()));
    connect(mScaleZ, SIGNAL(valueChanged(double)), this, SLOT(onScaleChanged()));
}

void TransformWidget::setTransform(const QVector3D& position, const QQuaternion& rotation, const QVector3D& scale) {
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
    emit transformChanged();
}

void TransformWidget::onRotationChanged() {
    emit transformChanged();
}

void TransformWidget::onScaleChanged() {
    emit transformChanged();
}

QDoubleSpinBox* TransformWidget::createDoubleSpinBox(double min, double max, double step, double value) {
    QDoubleSpinBox* spinBox = new QDoubleSpinBox();
    spinBox->setRange(min, max);
    spinBox->setSingleStep(step);
    spinBox->setValue(value);
    return spinBox;
}