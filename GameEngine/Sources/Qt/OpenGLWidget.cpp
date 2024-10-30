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

    
	mCurrentScene = new TestScene();
	mCurrentScene->load();


    elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();
}

OpenGLWidget::~OpenGLWidget()
{
    delete elapsedTimer;
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    
	mCurrentScene->create();
}

void OpenGLWidget::resizeGL(int w, int h) {
    if (h == 0) h = 1;

    // Update the projection matrix
    glViewport(0, 0, w, h);

	mCurrentScene->inputPublisher->resizeGLEvent(w, h);

}

void OpenGLWidget::paintGL() {
 	qint64 currentFrame = elapsedTimer->elapsed();
    deltaTime = (currentFrame - lastFrame) / 1000.0f; // Convert milliseconds to seconds
    lastFrame = currentFrame;

    mCurrentScene->init();

	mCurrentScene->inputPublisher->update(deltaTime);
	mCurrentScene->update(deltaTime);
	mCurrentScene->render();
}

void OpenGLWidget::keyPressEvent(QKeyEvent* event) {
	mCurrentScene->inputPublisher->keyPressEvent(event);
    
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent* event) {
	mCurrentScene->inputPublisher->keyReleaseEvent(event);
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
	mCurrentScene->inputPublisher->mouseMoveEvent(event);
}