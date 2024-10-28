// MainWindow.cpp
#include "Qt/MainWindow.h"
#include "Qt/OpenGLWidget.h"
#include <QTextEdit>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    createDockWidgets();
}

MainWindow::~MainWindow() {}

void MainWindow::createDockWidgets() {
    // Create the hierarchy dock widget
    hierarchyDock = new QDockWidget(tr("Hierarchy"), this);
    hierarchyView = new QTreeWidget();
    hierarchyView->setHeaderLabel("Nodes");
    hierarchyDock->setWidget(hierarchyView);
    hierarchyDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Create the camera view dock widget
    cameraViewDock = new QDockWidget(tr("Camera View"), this);
    OpenGLWidget* openGLWidget = new OpenGLWidget(this); // Create an instance of OpenGLWidget
    cameraViewDock->setWidget(openGLWidget);
    cameraViewDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Create the inspector dock widget
    inspectorDock = new QDockWidget(tr("Inspector"), this);
    inspectorView = new QWidget();
    inspectorDock->setWidget(inspectorView);
    inspectorDock->setAllowedAreas(Qt::AllDockWidgetAreas);

    // Add dock widgets to the main window
    addDockWidget(Qt::RightDockWidgetArea, hierarchyDock);
    addDockWidget(Qt::LeftDockWidgetArea, cameraViewDock);
    addDockWidget(Qt::RightDockWidgetArea, inspectorDock);

    // Connect signals
    connect(hierarchyView, &QTreeWidget::itemSelectionChanged, [this]() {
        QTreeWidgetItem* selectedItem = hierarchyView->currentItem();
        if (selectedItem) {
            updateInspectorView(selectedItem);
        }
        });

    // Populate the hierarchy view
    populateHierarchyView();
}

void MainWindow::populateHierarchyView() {
    // Example nodes, replace with actual nodes from your scene
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(hierarchyView, QStringList("Root"));
    QTreeWidgetItem* childItem1 = new QTreeWidgetItem(rootItem, QStringList("Child 1"));
    QTreeWidgetItem* childItem2 = new QTreeWidgetItem(rootItem, QStringList("Child 2"));
    hierarchyView->addTopLevelItem(rootItem);
}

void MainWindow::updateInspectorView(QTreeWidgetItem* item) {
    // Clear the inspector view
    QLayout* layout = inspectorView->layout();
    

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

    inspectorView->setLayout(layout);
}