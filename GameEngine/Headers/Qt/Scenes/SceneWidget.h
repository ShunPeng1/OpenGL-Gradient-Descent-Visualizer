#pragma once

#include <QDockWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QVBoxLayout>

#include "Engine/Scenes/SceneManager.h"
#include "OpenGLWidget.h"

class SceneWidget : public QDockWidget {
    Q_OBJECT

public:
    SceneWidget(const QString& title, SceneManager* sceneManager, QWidget* parent = nullptr);
    ~SceneWidget();
private slots:
    void onCameraChanged(int index);
    void onResolutionChanged();

private:
    SceneManager* mSceneManager;
    OpenGLWidget* mOpenGLWidget;
    QComboBox* mCameraDropdown;
    QSpinBox* mWidthSpinBox;
    QSpinBox* mHeightSpinBox;
};
