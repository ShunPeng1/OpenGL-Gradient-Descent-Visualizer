#include "Qt/Inspector/InspectorWidget.h"

InspectorWidget::InspectorWidget(QWidget* parent) : QWidget(parent) {
    mLayout = new QVBoxLayout();
    mLayout->setAlignment(Qt::AlignTop);
    setLayout(mLayout);
}

void InspectorWidget::updateInspectorView(QTreeWidgetItem* item) {
    // Clear the inspector view
    QLayoutItem* child;
    while ((child = mLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // Delete the widget
        delete child; // Delete the layout item
    }

    // Example properties, replace with actual properties of the selected node
    QLabel* nameLabel = new QLabel("Name: " + item->text(0));
    mLayout->addWidget(nameLabel);
}

