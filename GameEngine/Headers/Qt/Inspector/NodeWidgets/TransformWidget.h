#ifndef TRANSFORM_WIDGET_H
#define TRANSFORM_WIDGET_H

#include <QWidget>
#include <QVector3D>
#include <QQuaternion>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <memory>
#include "Engine/Components/Transform.h"
#include "Qt/Widgets/SectionWidget.h"
#include "Qt/Layouts/VectorFieldLayout.h"

class TransformWidget : public QWidget {
    Q_OBJECT

public:
    TransformWidget(Transform* transform, QWidget* parent = nullptr);
    ~TransformWidget();
    void setTransform(Transform* transform);
    void clearTransform();

private slots:
    void onPositionChanged(QVector3D);
    void onRotationChanged(QQuaternion);
    void onScaleChanged(QVector3D);
    void onPositionSet(double);
    void onRotationSet(double);
    void onScaleSet(double);

private:
    void updateUI();
    void connectSignals();
    void disconnectSignals();

private:
    bool mIsUpdating;
    Transform* mTransform;

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