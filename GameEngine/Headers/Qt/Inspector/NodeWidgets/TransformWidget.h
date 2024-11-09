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

class TransformWidget : public QWidget {
    Q_OBJECT

public:
    TransformWidget(QWidget* parent = nullptr);
    void setTransform(const QVector3D& position, const QQuaternion& rotation, const QVector3D& scale);
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
    QDoubleSpinBox* createDoubleSpinBox(double min, double max, double step, double value);

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