#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include "Engine/Renders/ShaderProgram.h"
#include "Engine/Renders/Mesh.h"
#include "Engine/Loaders/ModelLoader.h"
#include "Engine/GameObjects/Camera.h"
#include "TestGame/Controllers/FPSCameraController.h"
#include "Engine/Enums/RenderMode.h"


class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget* parent = nullptr);
	~OpenGLWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void updateInput();
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    ShaderProgram* defaultShader;
    ModelLoader* loader;
    Mesh* teapot;
	Mesh* triangle;
	Mesh* quad;
    Mesh* circle;
	Mesh* cube;
	Mesh* sphere;
	Mesh* icosphere;
	Mesh* cylinder;
	Mesh* cone;
    Mesh* plane;
	

    // Add other models...
    Camera* camera;
    FPSCameraController* cameraController;

    bool firstMouse;
    float deltaTime;
    float lastFrame;
    bool spacePressed;
    int currentModel;
    PolygonMode currentRenderMode;
  
    QElapsedTimer* elapsedTimer;
    QMap<int, bool> keyStates;
};

#endif // OPENGLWIDGET_H