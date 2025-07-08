#include "Qt/Inspector/NodeWidgets/TransformWidget.h"
#include <cmath>

TransformWidget::TransformWidget(Transform* transform, QWidget* parent) : INodeWidget<Transform>(parent) {
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

    setNode(transform);
}

TransformWidget::~TransformWidget()
{
    clearNode();
}

void TransformWidget::setNode(Transform* transform) {
    disconnectSignals();
    
    mNode = transform;

    updateUI();
    connectSignals();
}

void TransformWidget::clearNode() {
    disconnectSignals();
    
    mNode = nullptr;
}

void TransformWidget::onPositionChanged(QVector3D position)
{
    blockSignals(true);
	mPosX->setValue(position.x());
	mPosY->setValue(position.y());
	mPosZ->setValue(position.z());
    blockSignals(false);
}

void TransformWidget::onRotationChanged(QQuaternion rotation)
{
    blockSignals(true);
	QVector3D euler = rotation.toEulerAngles();
	mRotX->setValue(euler.x());
	mRotY->setValue(euler.y());
	mRotZ->setValue(euler.z());
    blockSignals(false);
}

void TransformWidget::onScaleChanged(QVector3D scale)
{
    blockSignals(true);
	mScaleX->setValue(scale.x());
	mScaleY->setValue(scale.y());
	mScaleZ->setValue(scale.z());
    blockSignals(false);
}


void TransformWidget::onPositionSet(double value) {
	QVector3D position(mPosX->value(), mPosY->value(), mPosZ->value());
    mNode->setLocalPosition(position);
}

void TransformWidget::onRotationSet(double value) {
    QQuaternion rotation = QQuaternion::fromEulerAngles(mRotX->value(), mRotY->value(), mRotZ->value());
    mNode->setLocalRotation(rotation);
}

void TransformWidget::onScaleSet(double value) {
	QVector3D scale(mScaleX->value(), mScaleY->value(), mScaleZ->value());
    mNode->setLocalScale(scale);
}

void TransformWidget::updateUI() {
	blockSignals(true);
    if (mNode) {
        QVector3D position = mNode->getLocalPosition();
        QQuaternion rotation = mNode->getLocalRotation();
        QVector3D scale = mNode->getLocalScale();

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
	blockSignals(false);
}

void TransformWidget::connectSignals() {
    if (!mNode){
        return;
    }

	connect(mNode, &Transform::positionChanged, this, &TransformWidget::onPositionChanged);
	connect(mNode, &Transform::rotationChanged, this, &TransformWidget::onRotationChanged);
	connect(mNode, &Transform::scaleChanged, this, &TransformWidget::onScaleChanged);
}

void TransformWidget::disconnectSignals() {
    if (!mNode) {
        return;
    }

	disconnect(mNode, &Transform::positionChanged, this, &TransformWidget::onPositionChanged);
	disconnect(mNode, &Transform::rotationChanged, this, &TransformWidget::onRotationChanged);
	disconnect(mNode, &Transform::scaleChanged, this, &TransformWidget::onScaleChanged);
}

void TransformWidget::blockSignals(bool block) {
    mPosX->blockSignals(block);
    mPosY->blockSignals(block);
    mPosZ->blockSignals(block);
    mRotX->blockSignals(block);
    mRotY->blockSignals(block);
    mRotZ->blockSignals(block);
    mScaleX->blockSignals(block);
    mScaleY->blockSignals(block);
    mScaleZ->blockSignals(block);
}