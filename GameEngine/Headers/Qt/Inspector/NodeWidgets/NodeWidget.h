#ifndef NODE_WIDGET_H
#define NODE_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "Engine/Scenes/Node.h"
#include "Qt/Widgets/SectionWidget.h"
#include "Qt/Layouts/VectorFieldLayout.h"


class NodeWidget : public QWidget {
    Q_OBJECT

public:
    NodeWidget(Node* node, QWidget* parent = nullptr);
    ~NodeWidget();
    void setNode(Node* node);
    void clearNode();

private slots:
    void onIsAliveChanged(bool isAlive);
    void onObjectNameChanged(const QString& name);

	void onIsAliveSet(bool isAlive);
	void onObjectNameSet(const QString& name);

private:
    void updateUI();
    void connectSignals();
    void disconnectSignals();

private:
    Node* mNode;

    SectionWidget* mSection;

    QLineEdit* mNameEdit;
    QCheckBox* mIsAliveCheckBox;
};

#endif // NODE_WIDGET_H