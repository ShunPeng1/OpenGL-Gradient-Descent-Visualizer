#include "Qt/Inspector/NodeWidgets/CameraWidget.h"
CameraWidget::CameraWidget(Camera* camera, QWidget* parent)
    : INodeWidget<Camera>(parent){

    QVBoxLayout* widgetLayout = new QVBoxLayout(this);
    mSection = new SectionWidget("Camera", 0, this);
    widgetLayout->addWidget(mSection);

    QVBoxLayout* mainLayout = new QVBoxLayout(mSection);

    // FOV
    QHBoxLayout* fovLayout = new QHBoxLayout();
    QLabel* fovLabel = new QLabel("FOV:");
    mFov = new QDoubleSpinBox();
    mFov->setRange(1.0, 179.0);
    mFov->setSingleStep(1.0);
    fovLayout->addWidget(fovLabel);
    fovLayout->addWidget(mFov);
    mainLayout->addLayout(fovLayout);

    // Near
    QHBoxLayout* nearLayout = new QHBoxLayout();
    QLabel* nearLabel = new QLabel("Near:");
    mNear = new QDoubleSpinBox();
    mNear->setRange(0.01, 1000.0);
    mNear->setSingleStep(0.1);
    nearLayout->addWidget(nearLabel);
    nearLayout->addWidget(mNear);
    mainLayout->addLayout(nearLayout);

    // Far
    QHBoxLayout* farLayout = new QHBoxLayout();
    QLabel* farLabel = new QLabel("Far:");
    mFar = new QDoubleSpinBox();
    mFar->setRange(0.1, 10000.0);
    mFar->setSingleStep(1.0);
    farLayout->addWidget(farLabel);
    farLayout->addWidget(mFar);
    mainLayout->addLayout(farLayout);

    // Aspect Ratio
    QHBoxLayout* aspectRatioLayout = new QHBoxLayout();
    QLabel* aspectRatioLabel = new QLabel("Aspect Ratio:");
    mAspectRatio = new QDoubleSpinBox();
    mAspectRatio->setRange(0.1, 10.0);
    mAspectRatio->setSingleStep(0.1);
    aspectRatioLayout->addWidget(aspectRatioLabel);
    aspectRatioLayout->addWidget(mAspectRatio);
    mainLayout->addLayout(aspectRatioLayout);

    // Is Ortho
    QHBoxLayout* isOrthoLayout = new QHBoxLayout();
    QLabel* isOrthoLabel = new QLabel("Is Ortho:");
    mIsOrtho = new QCheckBox();
    isOrthoLayout->addWidget(isOrthoLabel);
    isOrthoLayout->addWidget(mIsOrtho);
    mainLayout->addLayout(isOrthoLayout);

	// Draw Frustum
	QHBoxLayout* drawFrustumLayout = new QHBoxLayout();
	QLabel* drawFrustumLabel = new QLabel("Draw Frustum:");
	mDrawFrustum = new QCheckBox();
	drawFrustumLayout->addWidget(drawFrustumLabel);
	drawFrustumLayout->addWidget(mDrawFrustum);
	mainLayout->addLayout(drawFrustumLayout);


    // Width
    QHBoxLayout* widthLayout = new QHBoxLayout();
    QLabel* widthLabel = new QLabel("Width:");
    mWidth = new QDoubleSpinBox();
    mWidth->setRange(0.1, 10000.0);
    mWidth->setSingleStep(1.0);
    widthLayout->addWidget(widthLabel);
    widthLayout->addWidget(mWidth);
    mainLayout->addLayout(widthLayout);

    mSection->setContentLayout(*mainLayout);

	// Connect signals
    connect(mFov, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onFovSet);
    connect(mNear, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onNearSet);
    connect(mFar, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onFarSet);
    connect(mAspectRatio, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onAspectRatioSet);
    connect(mIsOrtho, &QCheckBox::toggled, this, &CameraWidget::onIsOrthoSet);
	connect(mDrawFrustum, &QCheckBox::toggled, this, &CameraWidget::onDrawFrustumSet);
    connect(mWidth, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onWidthSet);

    setNode(camera);
}

CameraWidget::~CameraWidget() {
    clearNode();
}

void CameraWidget::setNode(Camera* camera) {
    disconnectSignals();
    mNode = camera;
    updateUI();
    connectSignals();
}

void CameraWidget::clearNode() {
    disconnectSignals();
    mNode = nullptr;
}

void CameraWidget::onFovChanged(float value) {
    mFov->setValue(value);
}

void CameraWidget::onNearChanged(float value) {
	mNear->setValue(value);
}

void CameraWidget::onFarChanged(float value) {
	mFar->setValue(value);
}

void CameraWidget::onAspectRatioChanged(float value) {
	mAspectRatio->setValue(value);
}

void CameraWidget::onIsOrthoChanged(bool checked) {
	mIsOrtho->setChecked(checked);
}

void CameraWidget::onWidthChanged(float value) {
	mWidth->setValue(value);
}

void CameraWidget::onDrawFrustumChanged(bool value)
{
	mDrawFrustum->setChecked(value);
}

void CameraWidget::onFovSet(double value)
{
	if (mNode) {
		mNode->setFov(value);
	}
}

void CameraWidget::onNearSet(double value)
{
	if (mNode) {
		mNode->setNear(value);
	}
}

void CameraWidget::onFarSet(double value)
{
	if (mNode) {
		mNode->setFar(value);
	}
}

void CameraWidget::onAspectRatioSet(double value)
{
    if (mNode) {
		mNode->setAspectRatio(value);
    }
}

void CameraWidget::onIsOrthoSet(bool value)
{
	if (mNode) {
		mNode->setIsOrtho(value);
	}
}

void CameraWidget::onWidthSet(double value)
{
    if (mNode) {
		mNode->setWidth(value);
    }
}

void CameraWidget::onDrawFrustumSet(bool value)
{
	if (mNode) {
		mNode->setDrawFrustum(value);
	}
}

void CameraWidget::updateUI() {
    blockSignals(true);
    if (mNode) {
        mFov->setValue(mNode->getFov());
        mNear->setValue(mNode->getNear());
        mFar->setValue(mNode->getFar());
        mAspectRatio->setValue(mNode->getAspectRatio());
        mIsOrtho->setChecked(mNode->getIsOrtho());
		mDrawFrustum->setChecked(mNode->getDrawFrustum());
        mWidth->setValue(mNode->getWidth());
    }
    else {
        mFov->setValue(60.0);
        mNear->setValue(0.1);
        mFar->setValue(1000.0);
        mAspectRatio->setValue(1.78);
        mIsOrtho->setChecked(false);
		mDrawFrustum->setChecked(false);
        mWidth->setValue(1.0);
    }
    blockSignals(false);
}

void CameraWidget::connectSignals() {
    if (!mNode) return;

	connect(mNode, &Camera::fovChanged, this, &CameraWidget::onFovChanged);
	connect(mNode, &Camera::nearChanged, this, &CameraWidget::onNearChanged);
	connect(mNode, &Camera::farChanged, this, &CameraWidget::onFarChanged);
	connect(mNode, &Camera::aspectRatioChanged, this, &CameraWidget::onAspectRatioChanged);
	connect(mNode, &Camera::isOrthoChanged, this, &CameraWidget::onIsOrthoChanged);
	connect(mNode, &Camera::drawFrustumChanged, this, &CameraWidget::onDrawFrustumChanged);
	connect(mNode, &Camera::widthChanged, this, &CameraWidget::onWidthChanged);
}

void CameraWidget::disconnectSignals() {
    if (!mNode) return;

	disconnect(mNode, &Camera::fovChanged, this, &CameraWidget::onFovChanged);
	disconnect(mNode, &Camera::nearChanged, this, &CameraWidget::onNearChanged);
	disconnect(mNode, &Camera::farChanged, this, &CameraWidget::onFarChanged);
	disconnect(mNode, &Camera::aspectRatioChanged, this, &CameraWidget::onAspectRatioChanged);
	disconnect(mNode, &Camera::isOrthoChanged, this, &CameraWidget::onIsOrthoChanged);
	disconnect(mNode, &Camera::drawFrustumChanged, this, &CameraWidget::onDrawFrustumChanged);
	disconnect(mNode, &Camera::widthChanged, this, &CameraWidget::onWidthChanged);
}

void CameraWidget::blockSignals(bool value)
{
	mFov->blockSignals(value);
	mNear->blockSignals(value);
	mFar->blockSignals(value);
	mAspectRatio->blockSignals(value);
	mIsOrtho->blockSignals(value);
	mDrawFrustum->blockSignals(value);
	mWidth->blockSignals(value);
}
