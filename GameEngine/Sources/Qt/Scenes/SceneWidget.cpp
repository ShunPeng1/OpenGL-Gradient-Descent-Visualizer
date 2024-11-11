#include "Qt/Scenes/SceneWidget.h"

SceneWidget::SceneWidget(const QString& title, SceneManager* sceneManager, QWidget* parent)
    : QDockWidget(title, parent), mSceneManager(sceneManager) {
    IScene* currentScene = mSceneManager->getCurrentScene();
    auto cameras = currentScene->getCameras();
    
    QWidget* mainContainer = new QWidget(this);
	QVBoxLayout* mainLayout = new QVBoxLayout(mainContainer);
	
	mOpenGLWidget = new OpenGLWidget(mSceneManager->getCurrentScene(), mainContainer);
	if (cameras.size() > 0) {
		mOpenGLWidget->setCurrentCamera(cameras[0]);
	}

    QWidget* topContainer = new QWidget(this);

	mainLayout->addWidget(topContainer); 
    mainLayout->addWidget(mOpenGLWidget);
    mainContainer->setLayout(mainLayout);


    QHBoxLayout* topLayout = new QHBoxLayout(topContainer);
    // Camera dropdown
    mCameraDropdown = new QComboBox(topContainer);
    // Populate with camera options (example)
    for (auto camera : cameras) {
        mCameraDropdown->addItem(camera->getName());
    }

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
	IScene* mCurrentScene = mSceneManager->getCurrentScene();
    auto cameras = mCurrentScene->getCameras();
    if (index >= 0 && index < cameras.size()) {
        mOpenGLWidget->setCurrentCamera(cameras[index]);
    }
}

void SceneWidget::onResolutionChanged() {
    int width = mWidthSpinBox->value();
    int height = mHeightSpinBox->value();
    mOpenGLWidget->resize(width, height);
}