#include "Qt/OpenGLWidget.h"
#include <QTimer>
#include <QApplication>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include <qdir.h>
#include <glm.hpp>
#include <ext/matrix_clip_space.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include "Engine/Render/Shader.h"
#include "Engine/Render/Mesh.h"
#include "Engine/Loader/ModelLoader.h"

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent), QOpenGLFunctions() {
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&OpenGLWidget::update));
    timer->start(16); // ~60 FPS

    // Initialize camera parameters
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
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
    defaultShader = new Shader(":/Resources/Shaders/default.vert", ":/Resources/Shaders/default.frag");
    defaultShader->Use();

    glm::mat4 world = glm::mat4(1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width() / (float)height(), 0.1f, 100.0f);
    glm::vec2 texScale = glm::vec2(1.0f, 1.0f);

    defaultShader->SetUniformMat4("mWorld", world);
    defaultShader->SetUniformMat4("mProj", proj);
    defaultShader->SetUniformVec2("mTexScale", texScale);
    defaultShader->SetUniformBool("mUseTexture", false);
    defaultShader->SetUniformBool("mUseColor", true);

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

}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL() {
 	qint64 currentFrame = elapsedTimer->elapsed();
    deltaTime = (currentFrame - lastFrame) / 1000.0f; // Convert milliseconds to seconds
    lastFrame = currentFrame;


    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	qDebug() << view[0].a << view[0].b << view[0].g << view[1].a << view[1].b << view[1].g << view[2].a << view[2].b << view[2].g << view[3].a << view[3].b << view[3].g;
    defaultShader->SetUniformMat4("mView", view);

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
}

void OpenGLWidget::keyPressEvent(QKeyEvent* event) {
    qDebug() << "Key Pressed: " << event->key();
    
    float cameraSpeed = 2.5 * deltaTime;
    if (event->key() == Qt::Key_W)
        cameraPos += cameraSpeed * cameraFront;
    if (event->key() == Qt::Key_S)
        cameraPos -= cameraSpeed * cameraFront;
    if (event->key() == Qt::Key_A)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (event->key() == Qt::Key_D)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (event->key() == Qt::Key_Q)
        cameraPos -= cameraSpeed * cameraUp;
    if (event->key() == Qt::Key_E)
        cameraPos += cameraSpeed * cameraUp;
    if (event->key() == Qt::Key_Escape)
        close();

    qDebug() << "Camera Position: " << cameraPos.x << cameraPos.y << cameraPos.z;

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
    if (event->key() == Qt::Key_Space) {
        spacePressed = false;
    }
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

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}