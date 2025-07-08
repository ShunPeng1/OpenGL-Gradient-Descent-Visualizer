// MainWindow.cpp
#include "Qt/MainWindow.h"

#include "TestGame/Scenes/TestScene.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    createScenes();
    createControlButtons();
    createDockWidgets();

}

MainWindow::~MainWindow() {

}

void MainWindow::createScenes() {
    mSceneManager = new SceneManager();

    IScene *firstScene = new TestScene();
    
	mSceneManager->addScene(firstScene);
	mSceneManager->changeToScene(firstScene);

    QOpenGLContext* context = QOpenGLContext::currentContext();
    QOpenGLContext * global = QOpenGLContext::globalShareContext();

}

void MainWindow::createDockWidgets() {
	IScene* currentScene = mSceneManager->getCurrentScene();

    // Create the hierarchy dock widget
    mHierarchyWidget = new HierarchyWidget(this);
    mHierarchyWidget->populateHierarchyView(currentScene);
    mHierarchyWidget->setAllowedAreas(Qt::AllDockWidgetAreas);


    // Create the camera view dock widget
    mSceneWidget = new SceneWidget(tr("Camera View"), mSceneManager, this);
    mSceneWidget->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Create the second camera view dock widget
	mSceneWidget2 = new SceneWidget(tr("Camera View 2"), mSceneManager, this);
	mSceneWidget2->setAllowedAreas(Qt::AllDockWidgetAreas);
	addDockWidget(Qt::LeftDockWidgetArea, mSceneWidget2);


    // Create the inspector dock widget
    mInspectorDock = new QDockWidget(tr("Inspector"), this);
    mInspectorWidget = new InspectorWidget(this);
    mInspectorDock->setWidget(mInspectorWidget);
    mInspectorDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Add dock widgets to the main window
    addDockWidget(Qt::LeftDockWidgetArea, mSceneWidget);
    addDockWidget(Qt::RightDockWidgetArea, mHierarchyWidget);
    addDockWidget(Qt::RightDockWidgetArea, mInspectorDock);

	// Enable dock nesting
    setDockNestingEnabled(true);


    // Connect signals
    connect(mHierarchyWidget, &HierarchyWidget::itemSelectionChanged, mInspectorWidget, &InspectorWidget::updateInspectorView);
}

void MainWindow::createControlButtons() {

}

void MainWindow::onPlayButtonClicked() {
	// TODO: Play the game logic
}

void MainWindow::onPauseButtonClicked() {
    // TODO: Pause the game logic
}