#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Engine/Nodes/Camera.h"
#include "Qt/Interfaces/INodeWidget.h"
#include "Qt/Widgets/SectionWidget.h"

class CameraWidget : public INodeWidget<Camera> {
    Q_OBJECT

public:
    CameraWidget(Camera* camera, QWidget* parent = nullptr);
    ~CameraWidget();

    void setNode(Camera* camera) override;
    void clearNode() override;

private slots:
    void onFovChanged(float);
    void onNearChanged(float);
    void onFarChanged(float);
    void onAspectRatioChanged(float);
    void onIsOrthoChanged(bool);
    void onWidthChanged(float);

	void onFovSet(double);
	void onNearSet(double);
	void onFarSet(double);
	void onAspectRatioSet(double);
	void onIsOrthoSet(bool);
	void onWidthSet(double);


private:
    void updateUI() override;
    void connectSignals() override;
    void disconnectSignals() override;
    void blockSignals(bool) override;

private:
    SectionWidget* mSection;

    QDoubleSpinBox* mFov;
    QDoubleSpinBox* mNear;
    QDoubleSpinBox* mFar;
    QDoubleSpinBox* mAspectRatio;
    QCheckBox* mIsOrtho;
    QDoubleSpinBox* mWidth;
};

#endif // CAMERA_WIDGET_H