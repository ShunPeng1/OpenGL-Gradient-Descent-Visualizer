#include "Qt/Inputs/InputPublisher.h"



InputPublisher::InputPublisher()
{
	mSubscribers = QList<InputSubscriber*>();
}

InputPublisher::~InputPublisher()
{
	clear();
}

void InputPublisher::subscribe(InputSubscriber* subscriber) {
    mSubscribers.append(subscriber);
}

void InputPublisher::unsubscribe(InputSubscriber* subscriber) {
    mSubscribers.removeOne(subscriber);
}

void InputPublisher::clear()
{
    mSubscribers.clear();
}

void InputPublisher::keyPressEvent(QKeyEvent* event) {
	for (const auto& subscriber : mSubscribers) {
		subscriber->updateKeyPress(event);
	}
}

void InputPublisher::keyReleaseEvent(QKeyEvent* event) {
	for (const auto& subscriber : mSubscribers) {
		subscriber->updateKeyRelease(event);
	}
}

void InputPublisher::resizeGLEvent(int w, int h)
{
	for (const auto& subscriber : mSubscribers) {
		subscriber->updateResizeGL(w, h);
	}
}

void InputPublisher::update(float deltaTime)
{
	for (const auto& subscriber : mSubscribers) {
		subscriber->update(deltaTime);
	}
}

void InputPublisher::mousePressEvent(QMouseEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateMousePress(event);
    }
}

void InputPublisher::mouseReleaseEvent(QMouseEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateMouseRelease(event);
    }
}

void InputPublisher::mouseDoubleClickEvent(QMouseEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateMouseDoubleClick(event);
    }
}

void InputPublisher::mouseMoveEvent(QMouseEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateMouseMove(event);
    }
}

#if QT_CONFIG(wheelevent)
void InputPublisher::wheelEvent(QWheelEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateWheel(event);
    }
}
#endif

void InputPublisher::focusInEvent(QFocusEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateFocusIn(event);
    }
}

void InputPublisher::focusOutEvent(QFocusEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateFocusOut(event);
    }
}

void InputPublisher::enterEvent(QEnterEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateEnter(event);
    }
}

void InputPublisher::leaveEvent(QEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateLeave(event);
    }
}

void InputPublisher::paintEvent(QPaintEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updatePaint(event);
    }
}

void InputPublisher::moveEvent(QMoveEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateMove(event);
    }
}

void InputPublisher::resizeEvent(QResizeEvent* event) {
    for (auto& subscriber : mSubscribers) {
        subscriber->updateResize(event);
    }
}

void InputPublisher::closeEvent(QCloseEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateClose(event);
    }
}

#ifndef QT_NO_CONTEXTMENU
void InputPublisher::contextMenuEvent(QContextMenuEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateContextMenu(event);
    }
}
#endif

#if QT_CONFIG(tabletevent)
void InputPublisher::tabletEvent(QTabletEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateTablet(event);
    }
}
#endif

#ifndef QT_NO_ACTION
void InputPublisher::actionEvent(QActionEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateAction(event);
    }
}
#endif

#if QT_CONFIG(draganddrop)
void InputPublisher::dragEnterEvent(QDragEnterEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateDragEnter(event);
    }
}

void InputPublisher::dragMoveEvent(QDragMoveEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateDragMove(event);
    }
}

void InputPublisher::dragLeaveEvent(QDragLeaveEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateDragLeave(event);
    }
}

void InputPublisher::dropEvent(QDropEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateDrop(event);
    }
}
#endif

void InputPublisher::showEvent(QShowEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateShow(event);
    }
}

void InputPublisher::hideEvent(QHideEvent* event) {
    for (const auto& subscriber : mSubscribers) {
        subscriber->updateHide(event);
    }
}
