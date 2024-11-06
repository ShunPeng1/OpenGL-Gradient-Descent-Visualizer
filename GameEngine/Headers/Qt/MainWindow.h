#pragma once

#include <Engine/Engine.h>

#include "Qt/Hierarchy/HierarchyWidget.h"
#include "Qt/Inspector/InspectorWidget.h"
#include "Qt/OpenGLWidget.h"

#include "Engine/Interfaces/IScene.h"

#include <QMainWindow>
#include <QDockWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onPlayButtonClicked();
    void onPauseButtonClicked();

private:
    void createDockWidgets();
    void createControlButtons();

private:
    QDockWidget* mCameraViewDock;
    QDockWidget* mInspectorDock;

    IScene* mPlayingScene;
    IScene* mEditingScene;

    HierarchyWidget* mHierarchyWidget;
    InspectorWidget* mInspectorWidget;
};