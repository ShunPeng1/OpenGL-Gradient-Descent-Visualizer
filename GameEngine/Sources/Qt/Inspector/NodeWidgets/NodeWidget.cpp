#include "Qt/Inspector/NodeWidgets/NodeWidget.h"

NodeWidget::NodeWidget(Node* node, QWidget* parent) : QWidget(parent), mNode() {
    QVBoxLayout* widgetLayout = new QVBoxLayout(this);

    SectionWidget* section = new SectionWidget("Node", 0, this);
    mSection = section;
    widgetLayout->addWidget(section);

    QVBoxLayout* mainLayout = new QVBoxLayout(section);
    // Name
    mNameEdit = new QLineEdit(this);
    mainLayout->addWidget(new QLabel("Name:"));
    mainLayout->addWidget(mNameEdit);

    // IsAlive
    mIsAliveCheckBox = new QCheckBox("Is Alive", this);
    mainLayout->addWidget(mIsAliveCheckBox);

	section->setContentLayout(*mainLayout);

    mNode = node;
    if (mNode) {
        mNameEdit->setText(mNode->getName());
        mIsAliveCheckBox->setChecked(mNode->getIsAlive());
    }


    connect(mNameEdit, &QLineEdit::textChanged, this, &NodeWidget::onNameChanged);
    connect(mIsAliveCheckBox, &QCheckBox::toggled, this, &NodeWidget::onIsAliveChanged);
}

NodeWidget::~NodeWidget() {}

void NodeWidget::setNode(Node* node) {
    mNode = node;
	mIsUpdating = true;
    if (node) {
        mNameEdit->setText(node->getName());
        mIsAliveCheckBox->setChecked(node->getIsAlive());
    }
	mIsUpdating = false;
}

void NodeWidget::clearNode() {
	mNode = nullptr;
    mNameEdit->clear();
    mIsAliveCheckBox->setChecked(false);
}

QString NodeWidget::getName() const {
    return mNameEdit->text();
}

bool NodeWidget::getIsAlive() const {
    return mIsAliveCheckBox->isChecked();
}

void NodeWidget::onIsAliveChanged(bool isAlive) {
	if (mIsUpdating) {
		return;
	}
    if (mNode) {
        if (isAlive) {
            mNode->revive();
        }
        else {
            mNode->kill();
        }
    }
}

void NodeWidget::onNameChanged(const QString& name) {
    if (mIsUpdating) {
        return;
    }
    if (mNode) {
        mNode->setName(name);
    }
}