#include "Qt/Inspector/NodeWidgets/CameraWidget.h"

CameraWidget::CameraWidget(Camera* camera, QWidget* parent) : QWidget(parent), mCamera(camera) {
    QVBoxLayout* widgetLayout = new QVBoxLayout(this);

    SectionWidget* section = new SectionWidget("Camera", 0, this);
    mSection = section;
    widgetLayout->addWidget(section);

    QVBoxLayout* mainLayout = new QVBoxLayout(section);

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

    // Width
    QHBoxLayout* widthLayout = new QHBoxLayout();
    QLabel* widthLabel = new QLabel("Width:");
    mWidth = new QDoubleSpinBox();
    mWidth->setRange(0.1, 10000.0);
    mWidth->setSingleStep(1.0);
    widthLayout->addWidget(widthLabel);
    widthLayout->addWidget(mWidth);
    mainLayout->addLayout(widthLayout);

    section->setContentLayout(*mainLayout);

    // Set the camera
    mCamera = camera;
    if (mCamera) {
        mFov->setValue(mCamera->getFov());
        mNear->setValue(mCamera->getNear());
        mFar->setValue(mCamera->getFar());
        mAspectRatio->setValue(mCamera->getAspectRatio());
        mIsOrtho->setChecked(mCamera->getIsOrtho());
        mWidth->setValue(mCamera->getWidth());
    }

    // Connect signals
    connect(mFov, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onFovChanged);
    connect(mNear, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onNearChanged);
    connect(mFar, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onFarChanged);
    connect(mAspectRatio, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onAspectRatioChanged);
    connect(mIsOrtho, &QCheckBox::toggled, this, &CameraWidget::onIsOrthoChanged);
    connect(mWidth, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &CameraWidget::onWidthChanged);
}

CameraWidget::~CameraWidget() {}

void CameraWidget::setCamera(Camera* camera) {
    mCamera = camera;
    mIsUpdating = true;
    if (mCamera) {
        mFov->setValue(mCamera->getFov());
        mNear->setValue(mCamera->getNear());
        mFar->setValue(mCamera->getFar());
        mAspectRatio->setValue(mCamera->getAspectRatio());
        mIsOrtho->setChecked(mCamera->getIsOrtho());
        mWidth->setValue(mCamera->getWidth());
    }
    mIsUpdating = false;
}

void CameraWidget::clearCamera() {
	mCamera = nullptr;
    mFov->setValue(45.0);
    mNear->setValue(0.1);
    mFar->setValue(1000.0);
    mAspectRatio->setValue(1.0);
    mIsOrtho->setChecked(false);
    mWidth->setValue(1.0);
}

float CameraWidget::getFov() const {
    return mFov->value();
}

float CameraWidget::getNear() const {
    return mNear->value();
}

float CameraWidget::getFar() const {
    return mFar->value();
}

float CameraWidget::getAspectRatio() const {
    return mAspectRatio->value();
}

bool CameraWidget::getIsOrtho() const {
    return mIsOrtho->isChecked();
}

float CameraWidget::getWidth() const {
    return mWidth->value();
}

void CameraWidget::onFovChanged() {
    if (mIsUpdating) {
        return;
    }
    if (mCamera) {
        mCamera->setFov(getFov());
    }
    emit cameraChanged();
}

void CameraWidget::onNearChanged() {
    if (mIsUpdating) {
        return;
    }
    if (mCamera) {
        mCamera->setNear(getNear());
    }
    emit cameraChanged();
}

void CameraWidget::onFarChanged() {
    if (mIsUpdating) {
        return;
    }
    if (mCamera) {
        mCamera->setFar(getFar());
    }
    emit cameraChanged();
}

void CameraWidget::onAspectRatioChanged() {
    if (mIsUpdating) {
        return;
    }
    if (mCamera) {
        mCamera->setAspectRatio(getAspectRatio());
    }
    emit cameraChanged();
}

void CameraWidget::onIsOrthoChanged() {
    if (mIsUpdating) {
        return;
    }
    if (mCamera) {
        mCamera->setIsOrtho(getIsOrtho());
    }
    emit cameraChanged();
}

void CameraWidget::onWidthChanged() {
    if (mIsUpdating) {
        return;
    }
    if (mCamera) {
        mCamera->setWidth(getWidth());
    }
    emit cameraChanged();
}