#pragma once

#include "Engine/Interfaces/IScene.h"
#include "Qt/Hierarchy/HierarchyItem.h"
#include <QDockWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>
class HierarchyWidget : public QDockWidget {
    Q_OBJECT

public:
    HierarchyWidget(QWidget* parent = nullptr);
    ~HierarchyWidget();

    void populateHierarchyView(IScene* scene);
    void updateInspectorView(QTreeWidgetItem* item);

signals:
    void itemSelectionChanged(QTreeWidgetItem* item);

private:
	void addChildren(QTreeWidgetItem* parent, Node* node);

private:
    QTreeWidget* mHierarchyTree;
};
