#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>

#include <Engine/Interfaces/IScene.h>


class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    OpenGLWidget(IScene* scene, QWidget* parent = nullptr);
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
    
    IScene* mCurrentScene;
	InputPublisher* mInputPublisher;

};

#endif // OPENGLWIDGET_H