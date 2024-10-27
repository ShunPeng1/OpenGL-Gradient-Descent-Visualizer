#ifndef INPUTPUBLISHER_H
#define INPUTPUBLISHER_H

#include "Qt/Inputs/InputState.h"
#include "Qt/Inputs/InputSubscriber.h"
#include <QObject>
#include <QKeyEvent>
#include <QMouseEvent>

class InputSubscriberData {
public:
	InputState state;
	InputSubscriber* subscriber;
};

class InputPublisher  {

private: 

    QList<InputSubscriber*> mSubscribers;

public:
	void subscribe(InputSubscriber* subscriber);
	void unsubscribe(InputSubscriber* subscriber);

	void clear();

    void resizeGLEvent(int w, int h);
    void update(float deltaTime);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent* event);
#endif
    void focusInEvent(QFocusEvent* event);
    void focusOutEvent(QFocusEvent* event);
    void enterEvent(QEnterEvent* event);
    void leaveEvent(QEvent* event);
    void paintEvent(QPaintEvent* event);
    void moveEvent(QMoveEvent* event);
    void resizeEvent(QResizeEvent* event);
    void closeEvent(QCloseEvent* event);
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent* event);
#endif
#if QT_CONFIG(tabletevent)
    void tabletEvent(QTabletEvent* event);
#endif
#ifndef QT_NO_ACTION
    void actionEvent(QActionEvent* event);
#endif
#if QT_CONFIG(draganddrop)
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent* event);
#endif
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);

};

#endif // INPUTPUBLISHER_H
