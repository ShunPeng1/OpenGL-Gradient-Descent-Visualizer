#pragma once

#include <Engine/Engine.h>
#include <QMainWindow>
#include <QDockWidget>
#include <QTabWidget>
#include "Engine/Interfaces/IScene.h"
#include "Qt/Hierarchy/HierarchyWidget.h"

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
    void updateInspectorView(QTreeWidgetItem* item);

private:
    QDockWidget* mCameraViewDock;
    QDockWidget* mInspectorDock;
    QWidget* mInspectorView;

    IScene* mPlayingScene;
    IScene* mEditingScene;

    HierarchyWidget* mHierarchyWidget;
};