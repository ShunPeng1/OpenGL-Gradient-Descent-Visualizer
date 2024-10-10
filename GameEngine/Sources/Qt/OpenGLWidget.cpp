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
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/Mesh.h"
#include "Engine/Loader/ModelLoader.h"


OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent), QOpenGLFunctions() {
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&OpenGLWidget::update));
    timer->start(16); // ~60 FPS

    // Initialize camera parameters
    cameraPos = QVector3D(0.0f, 0.0f, 3.0f);
    cameraFront = QVector3D(0.0f, 0.0f, -1.0f);
    cameraUp = QVector3D(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;
    firstMouse = true;
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    spacePressed = false;
    currentRenderMode = RenderMode::FACE;
    currentModel = 1;

	elapsedTimer = new QElapsedTimer();
    elapsedTimer->start();

    
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
    QMatrix4x4 proj;
    proj.perspective(45.0f, float(width()) / float(height()), 0.1f, 100.0f);
    QVector2D texScale(1.0f, 1.0f);

    defaultShader->setUniformValue("mWorld", world);
    defaultShader->setUniformValue("mProj", proj);
    defaultShader->setUniformValue("mTexScale", texScale);
    defaultShader->setUniformValue("mUseTexture", false);
    defaultShader->setUniformValue("mUseColor", true);

    ModelLoader tempLoader = ModelLoader::Builder().SetUseNormalColor(true).Build();
    loader = &tempLoader;

    teapot = tempLoader.LoadObjFile(":/Resources/Models/teapot.obj");
    triangle = tempLoader.LoadTriangle();
    quad = tempLoader.LoadQuad();
    cube = tempLoader.LoadCube();
    circle = tempLoader.LoadCircle(36);
    cylinder = tempLoader.LoadCylinder(36);
    sphere = tempLoader.LoadSphere(40, 40);
    icosphere = tempLoader.LoadIcosphere(5);
    cone = tempLoader.LoadCone(36);

	ModelLoader::Range xRange = ModelLoader::Range(-10.0f, 10.0f, 0.1f);
    ModelLoader::Range yRange = ModelLoader::Range(-10.0f, 10.0f, 0.1f);
	plane = tempLoader.LoadPlane([](float x, float y) -> float {
        return std::sin(x) * std::sin(y);
		}, xRange, yRange);
}

void OpenGLWidget::resizeGL(int w, int h) {
    if (h == 0) h = 1;
    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;

    glViewport(0, 0, w, h);

    // Update the projection matrix
    QMatrix4x4 proj;
    proj.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
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

    QMatrix4x4 view;
    view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    defaultShader->bind();
    defaultShader->setUniformValue("mView", view);

    // Draw the selected model
    switch (currentModel) {
    case 1: teapot->Draw(*defaultShader); break;
    case 2: triangle->Draw(*defaultShader); break;
    case 3: quad->Draw(*defaultShader); break;
    case 4: cube->Draw(*defaultShader); break;
    case 5: circle->Draw(*defaultShader); break;
    case 6: cylinder->Draw(*defaultShader); break;
    case 7: sphere->Draw(*defaultShader); break;
    case 8: cone->Draw(*defaultShader); break;
    case 9: plane->Draw(*defaultShader); break;
    case 0: icosphere->Draw(*defaultShader); break;
    }

    // Set the polygon mode based on the current rendering mode
    switch (currentRenderMode) {
    case RenderMode::FACE:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    case RenderMode::WIREFRAME:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case RenderMode::POINT:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    }

	defaultShader->release();
}
void OpenGLWidget::keyPressEvent(QKeyEvent* event) {
    keyStates[event->key()] = true;

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
        case RenderMode::FACE:
            currentRenderMode = RenderMode::WIREFRAME;
            break;
        case RenderMode::WIREFRAME:
            currentRenderMode = RenderMode::POINT;
            break;
        case RenderMode::POINT:
            currentRenderMode = RenderMode::FACE;
            break;
        }
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent* event) {
    keyStates[event->key()] = false;

    if (event->key() == Qt::Key_Space) {
        spacePressed = false;
    }
}

void OpenGLWidget::updateInput() {
    float cameraSpeed = 2.5 * deltaTime;
    if (keyStates[Qt::Key_W])
        cameraPos += cameraSpeed * cameraFront;
    if (keyStates[Qt::Key_S])
        cameraPos -= cameraSpeed * cameraFront;
    if (keyStates[Qt::Key_A])
        cameraPos -= QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
    if (keyStates[Qt::Key_D])
        cameraPos += QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
    if (keyStates[Qt::Key_Q])
        cameraPos -= cameraSpeed * cameraUp;
    if (keyStates[Qt::Key_E])
        cameraPos += cameraSpeed * cameraUp;


    
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
    if (firstMouse) {
        lastX = event->position().x();
        lastY = event->position().y();
        firstMouse = false;
    }

    float xoffset = event->position().x() - lastX;
    float yoffset = lastY - event->position().y(); // reversed since y-coordinates go from bottom to top
    lastX = event->position().x();
    lastY = event->position().y();

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    QVector3D front;
    front.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
    front.setY(sin(qDegreesToRadians(pitch)));
    front.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
    cameraFront = front.normalized();
}