#include "Qt/Scenes/SceneWidget.h"

SceneWidget::SceneWidget(const QString& title, SceneManager* sceneManager, QWidget* parent)
    : QDockWidget(title, parent), mSceneManager(sceneManager) {
	QWidget* mainContainer = new QWidget(this);
	QVBoxLayout* mainLayout = new QVBoxLayout(mainContainer);
	
	mOpenGLWidget = new OpenGLWidget(mSceneManager->getCurrentScene(), mainContainer);
    QWidget* topContainer = new QWidget(this);

	mainLayout->addWidget(topContainer); 
    mainLayout->addWidget(mOpenGLWidget);
    mainContainer->setLayout(mainLayout);


    QHBoxLayout* topLayout = new QHBoxLayout(topContainer);
    // Camera dropdown
    mCameraDropdown = new QComboBox(topContainer);
    // Populate with camera options (example)
    mCameraDropdown->addItem("Camera 1");
    mCameraDropdown->addItem("Camera 2");
    connect(mCameraDropdown, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SceneWidget::onCameraChanged);

    // Resolution width
    mWidthSpinBox = new QSpinBox(topContainer);
    mWidthSpinBox->setRange(1, 4096);
    mWidthSpinBox->setValue(mOpenGLWidget->width());
    connect(mWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &SceneWidget::onResolutionChanged);

    // Resolution height
    mHeightSpinBox = new QSpinBox(topContainer);
    mHeightSpinBox->setRange(1, 4096);
    mHeightSpinBox->setValue(mOpenGLWidget->height());
    connect(mHeightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &SceneWidget::onResolutionChanged);

    topLayout->addWidget(mCameraDropdown);
    topLayout->addWidget(mWidthSpinBox);
    topLayout->addWidget(mHeightSpinBox);
	topContainer->setMaximumHeight(50);
    topContainer->setLayout(topLayout);

    setWidget(mainContainer);
}

SceneWidget::~SceneWidget()
{
	delete mOpenGLWidget;

}

void SceneWidget::onCameraChanged(int index) {
    // Handle camera change
    // Example: mOpenGLWidget->setMainCamera(index);
}

void SceneWidget::onResolutionChanged() {
    int width = mWidthSpinBox->value();
    int height = mHeightSpinBox->value();
    mOpenGLWidget->resize(width, height);
}