#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include "Engine/Render/ShaderProgram.h"
#include "Engine/Render/Mesh.h"
#include "Engine/Loader/ModelLoader.h"

enum class RenderMode {
    FACE,
    WIREFRAME,
    POINT
};

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(QWidget* parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
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

    QVector3D cameraPos;
    QVector3D cameraFront;
    QVector3D cameraUp;
    float yaw;
    float pitch;
    float lastX;
    float lastY;
    bool firstMouse;
    float deltaTime;
    float lastFrame;
    bool spacePressed;

    int currentModel;
    RenderMode currentRenderMode;
  
    QElapsedTimer* elapsedTimer;
};

#endif // OPENGLWIDGET_H