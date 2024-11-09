#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <memory>

#include "Engine/Nodes/Camera.h"
#include "Qt/Widgets/SectionWidget.h"

class CameraWidget : public QWidget {
    Q_OBJECT

public:
    CameraWidget(Camera* camera, QWidget* parent = nullptr);
    ~CameraWidget();
    void setCamera(Camera* camera);
    void clearCamera();

    float getFov() const;
    float getNear() const;
    float getFar() const;
    float getAspectRatio() const;
    bool getIsOrtho() const;
    float getWidth() const;

signals:
    void cameraChanged();

private slots:
    void onFovChanged();
    void onNearChanged();
    void onFarChanged();
    void onAspectRatioChanged();
    void onIsOrthoChanged();
    void onWidthChanged();

private:
    bool mIsUpdating;

    Camera* mCamera;

    SectionWidget* mSection;

    QDoubleSpinBox* mFov;
    QDoubleSpinBox* mNear;
    QDoubleSpinBox* mFar;
    QDoubleSpinBox* mAspectRatio;
    QCheckBox* mIsOrtho;
    QDoubleSpinBox* mWidth;
};

#endif // CAMERA_WIDGET_H