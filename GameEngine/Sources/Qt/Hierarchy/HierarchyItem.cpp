#include "Qt/Hierarchy/HierarchyItem.h"

Node* HierarchyItem::getNode() {
	return mNode;
}

void HierarchyItem::setNode(Node* val) {
	mNode = val;

	setText(0, mNode->objectName());

}
