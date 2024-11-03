#pragma once


#include <QTreeWidgetItem>

#include "Engine/Scenes/Node.h"



class HierarchyItem : public QTreeWidgetItem {
private:
	Node* mNode;

public:

	Node* getNode();
	void setNode(Node* val);

};