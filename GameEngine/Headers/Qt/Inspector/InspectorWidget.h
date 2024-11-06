#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTreeWidgetItem>

class InspectorWidget : public QWidget {
    Q_OBJECT

public:
    InspectorWidget(QWidget* parent = nullptr);
    void updateInspectorView(QTreeWidgetItem* item);

private:
    QVBoxLayout* mLayout;
};