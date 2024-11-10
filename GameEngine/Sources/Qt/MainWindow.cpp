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
    mCameraViewDock = new QDockWidget(tr("Camera View"), this);
    OpenGLWidget* openGLWidget = new OpenGLWidget(currentScene, this); // Create an instance of OpenGLWidget
    mCameraViewDock->setWidget(openGLWidget);
    mCameraViewDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Create the second camera view dock widget
    mCameraViewDock2 = new QDockWidget(tr("Camera View 2"), this);
    OpenGLWidget* openGLWidget2 = new OpenGLWidget(currentScene, this); // Create another instance of OpenGLWidget with a new scene
    mCameraViewDock2->setWidget(openGLWidget2);
    mCameraViewDock2->setAllowedAreas(Qt::AllDockWidgetAreas);
	addDockWidget(Qt::LeftDockWidgetArea, mCameraViewDock2);


    // Create the inspector dock widget
    mInspectorDock = new QDockWidget(tr("Inspector"), this);
    mInspectorWidget = new InspectorWidget(this);
    mInspectorDock->setWidget(mInspectorWidget);
    mInspectorDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Add dock widgets to the main window
    addDockWidget(Qt::LeftDockWidgetArea, mCameraViewDock);
    addDockWidget(Qt::RightDockWidgetArea, mHierarchyWidget);
    addDockWidget(Qt::RightDockWidgetArea, mInspectorDock);

	// Enable dock nesting
    setDockNestingEnabled(true);


    // Connect signals
    connect(mHierarchyWidget, &HierarchyWidget::itemSelectionChanged, mInspectorWidget, &InspectorWidget::updateInspectorView);
}

void MainWindow::createControlButtons() {
    QWidget* controlWidget = new QWidget(this);
    QHBoxLayout* controlLayout = new QHBoxLayout();

    QPushButton* playButton = new QPushButton("Play", this);
    QPushButton* pauseButton = new QPushButton("Pause", this);

    controlLayout->addWidget(playButton);
    controlLayout->addWidget(pauseButton);
    controlLayout->setAlignment(Qt::AlignCenter);

    controlWidget->setLayout(controlLayout);
	setMenuWidget(controlWidget);


    connect(playButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseButtonClicked);
}

void MainWindow::onPlayButtonClicked() {
	// TODO: Play the game logic
}

void MainWindow::onPauseButtonClicked() {
    // TODO: Pause the game logic
}