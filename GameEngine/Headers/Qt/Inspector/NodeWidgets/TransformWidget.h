// TransformWidget.h
#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

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
    TransformWidget(QWidget* parent = nullptr);
    ~TransformWidget();
    void setTransform(std::shared_ptr<Transform> transform);
    void clearTransform();

    QVector3D getPosition() const;
    QQuaternion getRotation() const;
    QVector3D getScale() const;

signals:
    void transformChanged();

private slots:
    void onPositionChanged();
    void onRotationChanged();
    void onScaleChanged();

private:
    std::weak_ptr<Transform> mTransform;
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

#endif // TRANSFORMWIDGET_H