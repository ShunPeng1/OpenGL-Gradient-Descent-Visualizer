#include "Qt/Scenes/SceneWidget.h"

SceneWidget::SceneWidget(const QString& title, SceneManager* sceneManager, QWidget* parent)
    : QDockWidget(title, parent), mSceneManager(sceneManager), mSteepness(0.1) {
    IScene* currentScene = mSceneManager->getCurrentScene();
    auto cameras = currentScene->getCameraManager()->getCameras();

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
        mCameraDropdown->addItem(camera->objectName());
    }

    connect(mCameraDropdown, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SceneWidget::onCameraChanged);

    // Export image button
    mExportRGBImageButton = new QPushButton("Export RGB Image", topContainer);
    connect(mExportRGBImageButton, &QPushButton::clicked, this, &SceneWidget::onExportRGBImageClicked);
    
    // Export depth image button
    mExportDepthImageButton = new QPushButton("Export Depth Image", topContainer);
    connect(mExportDepthImageButton, &QPushButton::clicked, this, &SceneWidget::onExportDepthImageClicked);

    // Steepness slider
    mSteepnessSlider = new QSlider(Qt::Horizontal, topContainer);
    mSteepnessSlider->setRange(1, 100); // Example range
    mSteepnessSlider->setValue(10); // Default value
    connect(mSteepnessSlider, &QSlider::valueChanged, this, &SceneWidget::onSteepnessChanged);

    mSteepnessLabel = new QLabel(QString::number(mSteepness, 'f', 1), topContainer);

    topLayout->addWidget(mCameraDropdown);
    topLayout->addWidget(mExportRGBImageButton);
	topLayout->addWidget(mExportDepthImageButton); 
    topLayout->addWidget(mSteepnessSlider); 
    topLayout->addWidget(mSteepnessLabel);


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
    auto cameras = mCurrentScene->getCameraManager()->getCameras();
    if (index >= 0 && index < cameras.size()) {
        mOpenGLWidget->setCurrentCamera(cameras[index]);
    }
}

void SceneWidget::onExportRGBImageClicked() {
    // Request image capture
    mOpenGLWidget->makeCurrent();
    mOpenGLWidget->update();

	QImage image = mOpenGLWidget->grabFramebuffer();

    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG Files (*.png);;JPEG Files (*.jpg);;All Files (*)");
    if (!filePath.isEmpty()) {
        image.save(filePath);
    }
}

void SceneWidget::onExportDepthImageClicked() {
    // Request depth image capture
    mOpenGLWidget->makeCurrent();
    mOpenGLWidget->update();


    QImage image = mOpenGLWidget->grabFramebuffer();

    // Get the size of the OpenGL widget
	Camera* camera = mOpenGLWidget->getCurrentCamera();
    int width = image.width();
    int height = image.height();
    float near = camera->getNear(); // Near plane distance
    float far = camera->getFar(); // Far plane distance

    // Allocate buffer for depth values
    std::vector<float> depthBuffer(width * height);

    // Read the depth buffer
    glReadPixels(0, 0, width, height, GL_DEPTH_COMPONENT, GL_FLOAT, depthBuffer.data());

    // Convert depth buffer to QImage
    QImage depthImage(width, height, QImage::Format_Grayscale8);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float depthValue = depthBuffer[y * width + x];

            // Inverse the depth value
            //depthValue = 1.0f - depthValue;

            //depthValue = 2.0 * depthValue - 1.0;
            // Linearize the depth value (assuming perspective projection)
            depthValue = (2.0f * near * far) / (far + near - (depthValue) * (far - near));

            // Logisticize the depth value
            depthValue = 1.0f / (1.0f + exp(-mSteepness * (depthValue - 5)));

            depthBuffer[y * width + x] = depthValue;

        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float depthValue = depthBuffer[y * width + x];

            int depthInt = static_cast<int>((1 - depthValue) * 255.0f);
            depthImage.setPixel(x, height - 1 - y, qRgb(depthInt, depthInt, depthInt));
        }
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Save Depth Image", "", "PNG Files (*.png);;JPEG Files (*.jpg);;All Files (*)");
    if (!filePath.isEmpty()) {
        depthImage.save(filePath);
    }
}

void SceneWidget::onSteepnessChanged(int value)
{
    mSteepness = value / 100.0f;
    mSteepnessLabel->setText(QString::number(mSteepness, 'f', 2));
}
