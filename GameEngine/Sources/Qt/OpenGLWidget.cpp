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

void OpenGLWidget::initializeGL() {

    initializeOpenGLFunctions();
    mInputPublisher->clear();

	mCurrentScene->init();

    elapsedTimer->start();

}

void OpenGLWidget::resizeGL(int w, int h) {
    if (h == 0) h = 1;

    // Update the projection matrix
    glViewport(0, 0, w, h);

    mInputPublisher->resizeGLEvent(w, h);
	mCurrentScene->getInputPublisher()->resizeGLEvent(w, h);

}

void OpenGLWidget::paintGL() {
 	qint64 currentFrame = elapsedTimer->elapsed();
    deltaTime = (currentFrame - lastFrame) / 1000.0f; // Convert milliseconds to seconds
    lastFrame = currentFrame;

    mCurrentScene->start();

    mInputPublisher->update(deltaTime);
	mCurrentScene->getInputPublisher()->update(deltaTime);
	mCurrentScene->update(deltaTime);
	mCurrentScene->render();
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