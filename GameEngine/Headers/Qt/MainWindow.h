#pragma once

#include <Engine/Engine.h>

#include "Qt/Hierarchy/HierarchyWidget.h"
#include "Qt/Inspector/InspectorWidget.h"
#include "Qt/Scenes/SceneWidget.h"

#include "Engine/Scenes/SceneManager.h"
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
	void createScenes();
    void createDockWidgets();
    void createControlButtons();

private:

    SceneManager* mSceneManager;

    SceneWidget* mSceneWidget;
    SceneWidget* mSceneWidget2;


    HierarchyWidget* mHierarchyWidget;
    QDockWidget* mInspectorDock;
    InspectorWidget* mInspectorWidget;
};