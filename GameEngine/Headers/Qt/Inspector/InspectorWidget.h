#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <Qt/Hierarchy/HierarchyItem.h>

#include "Qt/Inspector/InspectorNodeVisitor.h"

class InspectorWidget : public QWidget {
    Q_OBJECT

public:
    InspectorWidget(QWidget* parent = nullptr);
    void updateInspectorView(HierarchyItem* item);

private:
    QVBoxLayout* mLayout;
	InspectorNodeVisitor* mVisitor;
};