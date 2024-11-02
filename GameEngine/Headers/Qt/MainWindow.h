// MainWindow.h
#include <Engine/Engine.h>
#include <QMainWindow>
#include <QDockWidget>
#include <QTabWidget>
#include <QTreeWidget>

#include "Engine/Interfaces/IScene.h"

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
    void populateHierarchyView();
    void updateInspectorView(QTreeWidgetItem* item);


private:
    QDockWidget* mHierarchyDock;
    QDockWidget* mCameraViewDock;
    QDockWidget* mInspectorDock;
    QTreeWidget* mHierarchyTree;
    QWidget* mInspectorView;


    IScene* mPlayingScene;
    IScene* mEditingScene;
};