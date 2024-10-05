#include "Qt/OpenGLWidget.h"
#include <QTimer>
#include <QApplication>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <glm.hpp>
#include <ext/matrix_clip_space.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include "Engine/Render/Shader.h"
#include "Engine/Render/Mesh.h"
#include "Engine/Loader/ModelLoader.h"

OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&OpenGLWidget::update));
    timer->start(16); // ~60 FPS
}

void OpenGLWidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

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
    Mesh tempTeapot = loader->LoadObjFile(":/Resources/Models/teapot.obj");
    teapot = &tempTeapot;

    // Load other models...
}

void OpenGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    defaultShader->SetUniformMat4("mView", view);

    // Draw the selected model
    switch (currentModel) {
    case 1: teapot->Draw(*defaultShader); break;
        // Add other cases...
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
    float cameraSpeed = 2.5f * deltaTime;
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

    // Change model based on key press
    if (event->key() == Qt::Key_1)
        currentModel = 1;
    // Add other key cases...

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