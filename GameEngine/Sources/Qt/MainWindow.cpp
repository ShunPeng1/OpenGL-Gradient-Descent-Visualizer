// MainWindow.cpp
#include "Qt/MainWindow.h"

#include "TestGame/Scenes/TestScene.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), mPlayingScene(new Scene()), mEditingScene(nullptr) {

    mEditingScene = new TestScene();
    mEditingScene->load();

    createControlButtons();
    createDockWidgets();

}

MainWindow::~MainWindow() {
    delete mPlayingScene;
    if (mEditingScene) {
        delete mEditingScene;
    }
}


void MainWindow::createDockWidgets() {
    // Create the hierarchy dock widget
    mHierarchyWidget = new HierarchyWidget(this);
    mHierarchyWidget->populateHierarchyView(mEditingScene);
    mHierarchyWidget->setAllowedAreas(Qt::AllDockWidgetAreas);


    // Create the camera view dock widget
    mCameraViewDock = new QDockWidget(tr("Camera View"), this);
    OpenGLWidget* openGLWidget = new OpenGLWidget(mEditingScene, this); // Create an instance of OpenGLWidget
    mCameraViewDock->setWidget(openGLWidget);
    mCameraViewDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Create the inspector dock widget
    mInspectorDock = new QDockWidget(tr("Inspector"), this);
    mInspectorWidget = new InspectorWidget(this);
    mInspectorDock->setWidget(mInspectorWidget);
    mInspectorDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Add dock widgets to the main window
    addDockWidget(Qt::LeftDockWidgetArea, mCameraViewDock);
    addDockWidget(Qt::RightDockWidgetArea, mHierarchyWidget);
    addDockWidget(Qt::RightDockWidgetArea, mInspectorDock);

	//  
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
    if (!mEditingScene) {
        mEditingScene = mPlayingScene->clone(); // Duplicate the current scene
    }
    // Start the game logic
}

void MainWindow::onPauseButtonClicked() {
    if (mEditingScene) {
        delete mPlayingScene;
        mPlayingScene = mEditingScene->clone(); // Restore the backup scene
        delete mEditingScene;
        mEditingScene = nullptr;
    }
    // Pause the game logic
}