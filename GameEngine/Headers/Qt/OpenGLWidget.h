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
#include "Engine/Nodes/Camera.h"

#include "TestGame/Scenes/TestScene.h"
#include "TestGame/Controllers/FPSCameraController.h"


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
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    float deltaTime;
    float lastFrame;
    QElapsedTimer* elapsedTimer;
    
	Scene* mCurrentScene;

};

#endif // OPENGLWIDGET_H