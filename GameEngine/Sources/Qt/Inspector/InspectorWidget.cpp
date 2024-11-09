#include "Qt/Inspector/InspectorWidget.h"

InspectorWidget::InspectorWidget(QWidget* parent) : QWidget(parent) {
    mLayout = new QVBoxLayout();
    mLayout->setAlignment(Qt::AlignTop);
    setLayout(mLayout);


	mVisitor = new InspectorNodeVisitor();
}

void InspectorWidget::updateInspectorView(HierarchyItem* item) {
    // Clear the inspector view
    QLayoutItem* child;
    while ((child = mLayout->takeAt(0)) != nullptr) {
        delete child->widget(); // Delete the widget
        delete child; // Delete the layout item
    }

    Node* node = item->getNode();
    if (node) {
        mVisitor->clearStackItems();

        node->accept(mVisitor);

        const QList<QWidget*>& stackItems = mVisitor->getStackItems();
        for (QWidget* widget : stackItems) {
            mLayout->addWidget(widget);
        }
    
    }
}

