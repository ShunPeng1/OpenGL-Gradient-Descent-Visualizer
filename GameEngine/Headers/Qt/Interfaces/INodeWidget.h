#pragma once

#include <QWidget>

template <typename T>
class INodeWidget : public QWidget {
public:
    INodeWidget(QWidget* parent = nullptr) : QWidget(parent) {}

    virtual void setNode(T* node) = 0;
    virtual void clearNode() = 0;

protected:
    virtual void updateUI() = 0;
    virtual void connectSignals() = 0;
    virtual void disconnectSignals() = 0;
    virtual void blockSignals(bool) = 0;

protected:
	T* mNode;

};
