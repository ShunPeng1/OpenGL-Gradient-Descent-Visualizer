#include "Qt/Inspector/NodeWidgets/NodeWidget.h"

NodeWidget::NodeWidget(Node* node, QWidget* parent) : INodeWidget(parent), mNode() {
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

    connect(mNameEdit, &QLineEdit::textEdited, this, &NodeWidget::onObjectNameSet);
    connect(mIsAliveCheckBox, &QCheckBox::clicked, this, &NodeWidget::onIsAliveSet);

	setNode(node);
}

NodeWidget::~NodeWidget() 
{
    disconnectSignals();
}

void NodeWidget::setNode(Node* node) {

    disconnectSignals();
    
    mNode = node;

    updateUI();
	connectSignals();
}

void NodeWidget::clearNode() {
    disconnectSignals();

	mNode = nullptr;

	updateUI();
}

void NodeWidget::onIsAliveChanged(bool isAlive) {
    mIsAliveCheckBox->setChecked(isAlive);
}

void NodeWidget::onObjectNameChanged(const QString& name) {
    mNameEdit->setText(name);
}

void NodeWidget::onIsAliveSet(bool isAlive)
{
    if (mNode) {
        if (isAlive) {
            mNode->revive();
        }
        else {
            mNode->kill();
        }
    }
}

void NodeWidget::onObjectNameSet(const QString& name)
{
    if (mNode) {
        mNode->setObjectName(name);
    }
}

void NodeWidget::updateUI()
{
	if (mNode) {
		mNameEdit->setText(mNode->objectName());
		mIsAliveCheckBox->setChecked(mNode->getIsAlive());
	}
    else {
		mNameEdit->clear();
		mIsAliveCheckBox->setChecked(false);
    }
}

void NodeWidget::connectSignals()
{
	if (!mNode) {
		return;
	}
    connect(mNode, &Node::objectNameChanged, this, &NodeWidget::onObjectNameChanged);
    connect(mNode, &Node::isAliveChanged, this, &NodeWidget::onIsAliveChanged);
}

void NodeWidget::disconnectSignals()
{
	if (!mNode) {
		return;
	}

	disconnect(mNode, &Node::objectNameChanged, this, &NodeWidget::onObjectNameChanged);
	disconnect(mNode, &Node::isAliveChanged, this, &NodeWidget::onIsAliveChanged);
}

void NodeWidget::blockSignals(bool)
{
	mNameEdit->blockSignals(true);
	mIsAliveCheckBox->blockSignals(true);
}
