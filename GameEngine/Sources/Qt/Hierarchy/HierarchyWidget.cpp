#include "Qt/Hierarchy/HierarchyWidget.h"

HierarchyWidget::HierarchyWidget(QWidget* parent) : QDockWidget(tr("Hierarchy"), parent) {
    mHierarchyTree = new QTreeWidget();
    mHierarchyTree->setHeaderLabel("Scene View");
    setWidget(mHierarchyTree);
    setAllowedAreas(Qt::AllDockWidgetAreas);

    connect(mHierarchyTree, &QTreeWidget::itemSelectionChanged, [this]() {
        QTreeWidgetItem* selectedItem = mHierarchyTree->currentItem();
        if (selectedItem) {
            emit itemSelectionChanged(selectedItem);
        }
        });

}

HierarchyWidget::~HierarchyWidget() {
    // Destructor implementation if needed
}

void HierarchyWidget::addChildren(QTreeWidgetItem* parent, Node* node) {
    for (Node* child : node->getChildren()) {
        HierarchyItem* item = new HierarchyItem();
        item->setNode(child);
        parent->addChild(item);

        // Recursively add children
        addChildren(item, child);
    }
}

void HierarchyWidget::populateHierarchyView(IScene* scene) {
    if (!scene) return;

    // Example nodes, replace with actual nodes from your scene
    QTreeWidgetItem* sceneItem = new QTreeWidgetItem(mHierarchyTree, QStringList() << scene->getName());

    mHierarchyTree->addTopLevelItem(sceneItem);

    for (Node* node : scene->getNodes()) {
        HierarchyItem* item = new HierarchyItem();
        item->setNode(node);
        sceneItem->addChild(item);

        // Recursively add children
        addChildren(item, node);
    }
}

void HierarchyWidget::updateInspectorView(QTreeWidgetItem* item) {
    // Implementation for updating the inspector view
}
