#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include <glm.hpp>
#include <ext/matrix_clip_space.hpp>
#include <gtc/matrix_transform.hpp>
#include "Engine/Render/Shader.h"
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
    Shader* defaultShader;
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

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
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