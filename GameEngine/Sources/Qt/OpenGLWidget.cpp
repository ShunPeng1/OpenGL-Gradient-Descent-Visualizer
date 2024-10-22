#include "Qt/OpenGLWidget.h"
#include <QTimer>
#include <QApplication>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QDir.h>
#include <QMatrix4x4>
#include <QVector3D>
#include "Engine/Renders/ShaderProgram.h"
#include "Engine/Renders/Mesh.h"
#include "Engine/Loaders/ModelLoader.h"



OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent), QOpenGLFunctions() {
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&OpenGLWidget::update));
    timer->start(16); // ~60 FPS

    currentRenderMode = PolygonMode::FILL;
    currentModel = 1;

	elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();

	camera = new Camera();
	cameraController = new FPSCameraController(camera);
}

OpenGLWidget::~OpenGLWidget()
{
    delete camera;
    delete cameraController;
    delete elapsedTimer;
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    qInfo() << "OpenGL version: " << glGetString(GL_VERSION) << "Current Dir" << QDir::current().absolutePath().toStdString();

    // Initialize shaders, models, etc.
    defaultShader = new ShaderProgram(":/Resources/Shaders/default.vert", ":/Resources/Shaders/default.frag");
    defaultShader->bind();

    QMatrix4x4 world;
    world.setToIdentity();
	QMatrix4x4 proj = camera->getProjectionMatrix();
    QVector2D texScale(1.0f, 1.0f);

    defaultShader->setUniformValue("mWorld", world);
    defaultShader->setUniformValue("mProj", proj);
    defaultShader->setUniformValue("mTexScale", texScale);
    defaultShader->setUniformValue("mUseTexture", false);
    defaultShader->setUniformValue("mUseColor", true);

    ModelLoader tempLoader = ModelLoader::Builder().SetUseNormalColor(true).Build();
    loader = &tempLoader;

    teapot = tempLoader.loadObjFile(":/Resources/Models/teapot.obj");
    triangle = tempLoader.loadTriangle();
    quad = tempLoader.loadQuad();
    cube = tempLoader.loadCube();
    circle = tempLoader.loadCircle(36);
    cylinder = tempLoader.loadCylinder(36);
    sphere = tempLoader.loadSphere(40, 40);
    icosphere = tempLoader.loadIcosphere(5);
    cone = tempLoader.loadCone(36);

	ModelLoader::Range xRange = ModelLoader::Range(-10.0f, 10.0f, 0.1f);
    ModelLoader::Range yRange = ModelLoader::Range(-10.0f, 10.0f, 0.1f);
	plane = tempLoader.loadPlane([](float x, float y) -> float {
        return std::sin(x) * std::sin(y);
		}, xRange, yRange);
}

void OpenGLWidget::resizeGL(int w, int h) {
    if (h == 0) h = 1;
    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;

    glViewport(0, 0, w, h);

    // Update the projection matrix
    camera->setAspectRatio(aspectRatio);
	QMatrix4x4 proj = camera->getProjectionMatrix();
    defaultShader->bind();
    defaultShader->setUniformValue("mProj", proj);
}

void OpenGLWidget::paintGL() {
 	qint64 currentFrame = elapsedTimer->elapsed();
    deltaTime = (currentFrame - lastFrame) / 1000.0f; // Convert milliseconds to seconds
    lastFrame = currentFrame;

	updateInput();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 view = camera->getViewMatrix();

    defaultShader->bind();
    defaultShader->setUniformValue("mView", view);

    // Draw the selected model
    switch (currentModel) {
    case 1: triangle->draw(*defaultShader); break;
    case 2: sphere->draw(*defaultShader); break;
    case 3: icosphere->draw(*defaultShader); break;
    case 4: plane->draw(*defaultShader); break;
    case 5: circle->draw(*defaultShader); break;
    case 6: cylinder->draw(*defaultShader); break;
    case 7: cube->draw(*defaultShader); break;
    case 8: cone->draw(*defaultShader); break;
    case 9: plane->draw(*defaultShader); break;
    case 0: teapot->draw(*defaultShader); break;
    }

    // Set the polygon mode based on the current rendering mode
    switch (currentRenderMode) {
    case PolygonMode::FILL:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    case PolygonMode::LINE:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case PolygonMode::POINT:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    }

	defaultShader->release();
}
void OpenGLWidget::keyPressEvent(QKeyEvent* event) {
    keyStates[event->key()] = true;
    cameraController->handleKeyPress(event);

    // Change model based on key press
    if (event->key() == Qt::Key_1)
        currentModel = 1;
    if (event->key() == Qt::Key_2)
        currentModel = 2;
    if (event->key() == Qt::Key_3)
        currentModel = 3;
    if (event->key() == Qt::Key_4)
        currentModel = 4;
    if (event->key() == Qt::Key_5)
        currentModel = 5;
    if (event->key() == Qt::Key_6)
        currentModel = 6;
    if (event->key() == Qt::Key_7)
        currentModel = 7;
    if (event->key() == Qt::Key_8)
        currentModel = 8;
    if (event->key() == Qt::Key_9)
        currentModel = 9;
    if (event->key() == Qt::Key_0)
        currentModel = 0;

    // Toggle rendering mode
    if (event->key() == Qt::Key_Space && !spacePressed) {
        spacePressed = true;
        switch (currentRenderMode) {
        case PolygonMode::FILL:
            currentRenderMode = PolygonMode::LINE;
            break;
        case PolygonMode::LINE:
            currentRenderMode = PolygonMode::POINT;
            break;
        case PolygonMode::POINT:
            currentRenderMode = PolygonMode::FILL;
            break;
        }
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent* event) {
    cameraController->handleKeyRelease(event);

    if (event->key() == Qt::Key_Space) {
        spacePressed = false;
    }
}

void OpenGLWidget::updateInput() {
   
	cameraController->update(deltaTime);
    
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
    cameraController->handleMouseMove(event);
}