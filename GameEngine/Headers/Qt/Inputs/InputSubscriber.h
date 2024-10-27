#ifndef INPUTSUBSCRIBER_H
#define INPUTSUBSCRIBER_H

#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>

class InputSubscriber {

public:
	InputSubscriber() {};
	virtual ~InputSubscriber() {};
	virtual void update() {};
	virtual void update(float deltaTime) {};
	virtual void updateResizeGL(int w, int h) {};

	virtual void updateKeyPress(QKeyEvent* event) {};
	virtual void updateKeyRelease(QKeyEvent* event) {};
	virtual void updateResize(QResizeEvent* event) {};
    virtual void updateMousePress(QMouseEvent* event) {};
    virtual void updateMouseRelease(QMouseEvent* event) {};
    virtual void updateMouseDoubleClick(QMouseEvent* event) {};
    virtual void updateMouseMove(QMouseEvent* event) {};
    virtual void updateWheel(QWheelEvent* event) {};
    virtual void updateFocusIn(QFocusEvent* event) {};
    virtual void updateFocusOut(QFocusEvent* event) {};
    virtual void updateEnter(QEnterEvent* event) {};
    virtual void updateLeave(QEvent* event) {};
    virtual void updatePaint(QPaintEvent* event) {};
    virtual void updateMove(QMoveEvent* event) {};
    virtual void updateClose(QCloseEvent* event) {};
    virtual void updateContextMenu(QContextMenuEvent* event) {};
    virtual void updateTablet(QTabletEvent* event) {};
    virtual void updateAction(QActionEvent* event) {};
    virtual void updateDragEnter(QDragEnterEvent* event) {};
    virtual void updateDragMove(QDragMoveEvent* event) {};
    virtual void updateDragLeave(QDragLeaveEvent* event) {};
    virtual void updateDrop(QDropEvent* event) {};
    virtual void updateShow(QShowEvent* event) {};
    virtual void updateHide(QHideEvent* event) {};

};

#endif // INPUTSUBSCRIBER_H