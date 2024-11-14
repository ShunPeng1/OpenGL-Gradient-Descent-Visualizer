#include "Qt/Inspector/NodeWidgets/MeshRendererWidget.h"

MeshRendererWidget::MeshRendererWidget(MeshRenderer* meshRenderer, QWidget* parent)
    : INodeWidget<MeshRenderer>(parent) {

    QVBoxLayout* widgetLayout = new QVBoxLayout(this);
    mSection = new SectionWidget("Mesh Renderer", 0, this);
    widgetLayout->addWidget(mSection);

    QVBoxLayout* mainLayout = new QVBoxLayout(mSection);

    // Polygon Mode
    QHBoxLayout* polygonModeLayout = new QHBoxLayout();
    QLabel* polygonModeLabel = new QLabel("Polygon Mode:");
    mPolygonMode = new QComboBox(); 
    mPolygonMode->addItem("Fill", getPolygonModeIndex(PolygonMode::FILL));
    mPolygonMode->addItem("Line", getPolygonModeIndex(PolygonMode::LINE));
    mPolygonMode->addItem("Point", getPolygonModeIndex(PolygonMode::POINT));
    polygonModeLayout->addWidget(polygonModeLabel);
    polygonModeLayout->addWidget(mPolygonMode);
    mainLayout->addLayout(polygonModeLayout);

    // Draw Buffer Mode
    QHBoxLayout* drawBufferModeLayout = new QHBoxLayout();
    QLabel* drawBufferModeLabel = new QLabel("Draw Buffer Mode:");
    mDrawBufferMode = new QComboBox();
    mDrawBufferMode->addItem("Front", getDrawBufferModeIndex(DrawBufferMode::FRONT));
    mDrawBufferMode->addItem("Back", getDrawBufferModeIndex(DrawBufferMode::BACK));
    mDrawBufferMode->addItem("Front and Back", getDrawBufferModeIndex(DrawBufferMode::FRONT_AND_BACK));
    drawBufferModeLayout->addWidget(drawBufferModeLabel);
    drawBufferModeLayout->addWidget(mDrawBufferMode);
    mainLayout->addLayout(drawBufferModeLayout);

    mSection->setContentLayout(*mainLayout);

    // Connect signals
    connect(mPolygonMode, QOverload<int>::of(&QComboBox::activated), this, &MeshRendererWidget::onPolygonModeSet);
    connect(mDrawBufferMode, QOverload<int>::of(&QComboBox::activated), this, &MeshRendererWidget::onDrawBufferModeSet);


    setNode(meshRenderer);
}

MeshRendererWidget::~MeshRendererWidget() {
    clearNode();
}

void MeshRendererWidget::setNode(MeshRenderer* meshRenderer) {
    disconnectSignals();
    mNode = meshRenderer;
    updateUI();
    connectSignals();
}

void MeshRendererWidget::clearNode() {
    disconnectSignals();
    mNode = nullptr;
}


void MeshRendererWidget::onPolygonModeChanged(PolygonMode polygonMode)
{
    mPolygonMode->setCurrentIndex(getPolygonModeIndex(polygonMode));
}

void MeshRendererWidget::onDrawBufferModeChanged(DrawBufferMode drawBufferMode)
{
	mDrawBufferMode->setCurrentIndex(getDrawBufferModeIndex(drawBufferMode));
}

void MeshRendererWidget::onPolygonModeSet(int polygonMode) {
    if (mNode) {
		mNode->setPolygonMode(getPolygonMode(polygonMode));
    }
}

void MeshRendererWidget::onDrawBufferModeSet(int drawBufferMode) {
    if (mNode) {
		mNode->setDrawBufferMode(getDrawBufferMode(drawBufferMode));
    }
}


void MeshRendererWidget::updateUI() {
    blockSignals(true);
    if (mNode) {
		mPolygonMode->setCurrentIndex(getPolygonModeIndex(mNode->getPolygonMode()));
		mDrawBufferMode->setCurrentIndex(getDrawBufferModeIndex(mNode->getDrawBufferMode()));
    }
    else {
        mPolygonMode->setCurrentIndex(0);
        mDrawBufferMode->setCurrentIndex(2);
    }
    blockSignals(false);
}

void MeshRendererWidget::connectSignals() {
    if (!mNode) return;

	connect(mNode, &MeshRenderer::polygonModeChanged, this, &MeshRendererWidget::onPolygonModeChanged);
	connect(mNode, &MeshRenderer::drawBufferModeChanged, this, &MeshRendererWidget::onDrawBufferModeChanged);
}

void MeshRendererWidget::disconnectSignals() {
    if (!mNode) return;

	disconnect(mNode, &MeshRenderer::polygonModeChanged, this, &MeshRendererWidget::onPolygonModeChanged);
	disconnect(mNode, &MeshRenderer::drawBufferModeChanged, this, &MeshRendererWidget::onDrawBufferModeChanged);
}

void MeshRendererWidget::blockSignals(bool value) {
    mPolygonMode->blockSignals(value);
    mDrawBufferMode->blockSignals(value);
}

int MeshRendererWidget::getPolygonModeIndex(PolygonMode polygonMode)
{
    switch (polygonMode)
	{
	case PolygonMode::FILL:
		return 0;
	case PolygonMode::LINE:
		return 1;
	case PolygonMode::POINT:
		return 2;
	default:
		return 0;
	}
}

int MeshRendererWidget::getDrawBufferModeIndex(DrawBufferMode drawBufferMode)
{
	switch (drawBufferMode)
	{
	case DrawBufferMode::FRONT:
		return 0;
	case DrawBufferMode::BACK:
		return 1;
	case DrawBufferMode::FRONT_AND_BACK:
		return 2;
	default:
		return 0;
	}
}

PolygonMode MeshRendererWidget::getPolygonMode(int index)
{
	switch (index)
	{
	case 0:
		return PolygonMode::FILL;
	case 1:
		return PolygonMode::LINE;
	case 2:
		return PolygonMode::POINT;
	default:
		return PolygonMode::FILL;
	}
}

DrawBufferMode MeshRendererWidget::getDrawBufferMode(int index)
{
	switch (index)
	{
	case 0:
		return DrawBufferMode::FRONT;
	case 1:
		return DrawBufferMode::BACK;
	case 2:
		return DrawBufferMode::FRONT_AND_BACK;
	default:
		return DrawBufferMode::FRONT;
	}
}
