// MainWindow.cpp
#include "Qt/MainWindow.h"
#include "Qt/OpenGLWidget.h"
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

#include "TestGame/Scenes/TestScene.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), mPlayingScene(new Scene()), mEditingScene(nullptr) {

    mEditingScene = new TestScene();

    createDockWidgets();
    createControlButtons();

}

MainWindow::~MainWindow() {
    delete mPlayingScene;
    if (mEditingScene) {
        delete mEditingScene;
    }
}

void MainWindow::createDockWidgets() {
    // Create the hierarchy dock widget
    mHierarchyDock = new QDockWidget(tr("Hierarchy"), this);
    mHierarchyTree = new QTreeWidget();
    mHierarchyTree->setHeaderLabel("Nodes");
    mHierarchyDock->setWidget(mHierarchyTree);
    mHierarchyDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Create the camera view dock widget
    mCameraViewDock = new QDockWidget(tr("Camera View"), this);
    OpenGLWidget* openGLWidget = new OpenGLWidget(mEditingScene, this); // Create an instance of OpenGLWidget
    mCameraViewDock->setWidget(openGLWidget);
    mCameraViewDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Create the inspector dock widget
    mInspectorDock = new QDockWidget(tr("Inspector"), this);
    mInspectorView = new QWidget();
    mInspectorDock->setWidget(mInspectorView);
    mInspectorDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Add dock widgets to the main window
    addDockWidget(Qt::RightDockWidgetArea, mHierarchyDock);
    addDockWidget(Qt::LeftDockWidgetArea, mCameraViewDock);
    addDockWidget(Qt::RightDockWidgetArea, mInspectorDock);

    // Connect signals
    connect(mHierarchyTree, &QTreeWidget::itemSelectionChanged, [this]() {
        QTreeWidgetItem* selectedItem = mHierarchyTree->currentItem();
        if (selectedItem) {
            updateInspectorView(selectedItem);
        }
        });

    // Populate the hierarchy view
    populateHierarchyView();
}

void MainWindow::createControlButtons() {
    QWidget* controlWidget = new QWidget(this);
    QHBoxLayout* controlLayout = new QHBoxLayout(controlWidget);

    QPushButton* playButton = new QPushButton("Play", this);
    QPushButton* pauseButton = new QPushButton("Pause", this);

    controlLayout->addWidget(playButton);
    controlLayout->addWidget(pauseButton);
    controlLayout->setAlignment(Qt::AlignCenter);

    controlWidget->setLayout(controlLayout);
    setCentralWidget(controlWidget);

    connect(playButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::onPauseButtonClicked);
}

void MainWindow::populateHierarchyView() {
    // Example nodes, replace with actual nodes from your scene
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(mHierarchyTree, QStringList("Root"));
    QTreeWidgetItem* childItem1 = new QTreeWidgetItem(rootItem, QStringList("Child 1"));
    QTreeWidgetItem* childItem2 = new QTreeWidgetItem(rootItem, QStringList("Child 2"));
    mHierarchyTree->addTopLevelItem(rootItem);
}

void MainWindow::updateInspectorView(QTreeWidgetItem* item) {
    // Clear the inspector view
    QLayout* layout = mInspectorView->layout();

    if (layout) {
        QWidget* widget = layout->widget();
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr) {
            delete child->widget(); // Delete the widget
            delete child; // Delete the layout item
        }
        delete layout; // Delete the layout itself
    }

    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    // Example properties, replace with actual properties of the selected node
    QLabel* nameLabel = new QLabel("Name: " + item->text(0));
    layout->addWidget(nameLabel);

    mInspectorView->setLayout(layout);
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