#include "stdafx.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include "Qt/MainWindow.h"

int main(int argc, char* argv[])
{
#if defined(Q_OS_WIN) && QT_VERSION_CHECK(5, 6, 0) <= QT_VERSION && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec();
}