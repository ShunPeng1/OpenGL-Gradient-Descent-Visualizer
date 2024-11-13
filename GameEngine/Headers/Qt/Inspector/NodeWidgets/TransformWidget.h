#ifndef TRANSFORM_WIDGET_H
#define TRANSFORM_WIDGET_H

#include <QWidget>
#include <QVector3D>
#include <QQuaternion>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "Engine/Components/Transform.h"
#include "Qt/Interfaces/INodeWidget.h"

#include "Qt/Widgets/SectionWidget.h"
#include "Qt/Layouts/VectorFieldLayout.h"

class TransformWidget : public INodeWidget<Transform> {
    Q_OBJECT

public:
    TransformWidget(Transform* transform, QWidget* parent = nullptr);
    ~TransformWidget();

	void setNode(Transform* transform) override;
	void clearNode() override;

private slots:
    void onPositionChanged(QVector3D);
    void onRotationChanged(QQuaternion);
    void onScaleChanged(QVector3D);
    void onPositionSet(double);
    void onRotationSet(double);
    void onScaleSet(double);

private:
    void updateUI() override;
    void connectSignals() override;
    void disconnectSignals() override;
    void blockSignals(bool) override;

private:

    SectionWidget* mSection;

    QDoubleSpinBox* mPosX;
    QDoubleSpinBox* mPosY;
    QDoubleSpinBox* mPosZ;

    QDoubleSpinBox* mRotX;
    QDoubleSpinBox* mRotY;
    QDoubleSpinBox* mRotZ;

    QDoubleSpinBox* mScaleX;
    QDoubleSpinBox* mScaleY;
    QDoubleSpinBox* mScaleZ;
};

#endif // TRANSFORM_WIDGET_H