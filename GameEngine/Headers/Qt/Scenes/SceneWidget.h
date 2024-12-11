// SceneWidget.h

#pragma once

#include <QDockWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QSlider>
#include <QLabel>

#include "Engine/Scenes/SceneManager.h"
#include "OpenGLWidget.h"

class SceneWidget : public QDockWidget {
    Q_OBJECT

public:
    SceneWidget(const QString& title, SceneManager* sceneManager, QWidget* parent = nullptr);
    ~SceneWidget();

private slots:
    void onCameraChanged(int index);
    void onExportRGBImageClicked();
    void onExportDepthImageClicked();
    void onSteepnessChanged(int value);

private:
    SceneManager* mSceneManager;
    OpenGLWidget* mOpenGLWidget;
    QComboBox* mCameraDropdown;
    QPushButton* mExportRGBImageButton;
    QPushButton* mExportDepthImageButton;
    QSlider* mSteepnessSlider;
	QLabel* mSteepnessLabel;

	float mSteepness;
};