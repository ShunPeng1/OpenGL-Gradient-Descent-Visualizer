#include "Qt/Scenes/OpenGLWidget.h"
#include <QTimer>
#include <QApplication>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QDir.h>
#include <QMatrix4x4>
#include <QVector3D>


OpenGLWidget::OpenGLWidget(IScene* scene, QWidget* parent) : QOpenGLWidget(parent), QOpenGLFunctions() {
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&OpenGLWidget::update));
    timer->start(16); // ~60 FPS
    
	mInputPublisher = new InputPublisher();

	mCurrentScene = scene;

    elapsedTimer = new QElapsedTimer();

    
}

OpenGLWidget::~OpenGLWidget()
{
    delete elapsedTimer;
}

void OpenGLWidget::setCurrentCamera(Camera* camera)
{
	mRenderCamera = camera;
}

void OpenGLWidget::initializeGL() {

    initializeOpenGLFunctions();
    mInputPublisher->clear();

	mCurrentScene->init();

    elapsedTimer->start();

    // Initialize QOpenGLDebugLogger
    QOpenGLContext* context = QOpenGLContext::currentContext();
    if (context->hasExtension(QByteArrayLiteral("GL_KHR_debug"))) {
        QOpenGLDebugLogger* logger = new QOpenGLDebugLogger(this);
        if (logger->initialize()) {
            connect(logger, &QOpenGLDebugLogger::messageLogged, this, &OpenGLWidget::handleLoggedMessage);
            logger->startLogging(QOpenGLDebugLogger::SynchronousLogging);
        }
        else {
            qDebug() << "Failed to initialize QOpenGLDebugLogger";
        }
    }
    else {
        qDebug() << "GL_KHR_debug extension not available";
    }
}

void OpenGLWidget::resizeGL(int w, int h) {
    if (h == 0) h = 1;

    mInputPublisher->resizeGLEvent(w, h);
	mCurrentScene->getInputPublisher()->resizeGLEvent(w, h);

}

void OpenGLWidget::handleLoggedMessage(const QOpenGLDebugMessage& debugMessage) {
    qDebug() << "OpenGL Debug Message:" << debugMessage;
}

void OpenGLWidget::paintGL() {
    if (mRenderCamera == nullptr) 
        return;

 	qint64 currentFrame = elapsedTimer->elapsed();
    deltaTime = (currentFrame - lastFrame) / 1000.0f; // Convert milliseconds to seconds
    lastFrame = currentFrame;


    mCurrentScene->start();

    mInputPublisher->update(deltaTime);
	mCurrentScene->getInputPublisher()->update(deltaTime);
	mCurrentScene->update(deltaTime);
    mCurrentScene->setMainCamera(mRenderCamera);
	mCurrentScene->render();

    // Check for OpenGL errors
    GLenum error = GL_NO_ERROR;
    do {
        error = glGetError();
        if (error != GL_NO_ERROR) {
            qDebug() << "OpenGL Error:" << error;
        }
    } while (error != GL_NO_ERROR);
}

void OpenGLWidget::keyPressEvent(QKeyEvent* event) {
	mInputPublisher->keyPressEvent(event);
	mCurrentScene->getInputPublisher()->keyPressEvent(event);
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent* event) {
    mInputPublisher->keyReleaseEvent(event);
	mCurrentScene->getInputPublisher()->keyReleaseEvent(event);
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
    mInputPublisher->mouseMoveEvent(event);
	mCurrentScene->getInputPublisher()->mouseMoveEvent(event);
}