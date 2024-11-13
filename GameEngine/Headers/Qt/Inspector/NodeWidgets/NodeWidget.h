#ifndef NODE_WIDGET_H
#define NODE_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "Engine/Scenes/Node.h"
#include "Qt/Interfaces/INodeWidget.h"
#include "Qt/Widgets/SectionWidget.h"
#include "Qt/Layouts/VectorFieldLayout.h"

class NodeWidget : public INodeWidget<Node> {
    Q_OBJECT

public:
    NodeWidget(Node* node, QWidget* parent = nullptr);
    ~NodeWidget();
    void setNode(Node* node) override;
    void clearNode() override;

private slots:
    void onIsAliveChanged(bool isAlive);
    void onObjectNameChanged(const QString& name);

	void onIsAliveSet(bool isAlive);
	void onObjectNameSet(const QString& name);

private:
    void updateUI() override;
    void connectSignals() override;
    void disconnectSignals() override;
    void blockSignals(bool) override;

private:
    Node* mNode;

    SectionWidget* mSection;

    QLineEdit* mNameEdit;
    QCheckBox* mIsAliveCheckBox;
};

#endif // NODE_WIDGET_H