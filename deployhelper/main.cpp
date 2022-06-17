#include <QCoreApplication>
#include <QtGui>
#include <QLocalServer>
#include <QtOpenGL>
#include <QGeoPositionInfoSource>
#include <QPrinterInfo>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QQuickWidget>
#include <QSqlDatabase>
#include <QTest>
#include <QUiLoader>
#include <QWebChannel>
#include <QWebEngineUrlScheme>
#include <QWebEngineSettings>
#include <QWebSocket>
#include <QStyle>
#include <QtWinExtras/QtWin>

#include <iostream>

#define L(X) std::cout << ((intptr_t) X)

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    L(QWindow::fromWinId);  // Gui
    L(QLocalServer::removeServer);  // Network
    L(QGLFormat::defaultFormat);    // OpenGL
    L(QGeoPositionInfoSource::availableSources);    // Positioning
    L(QPrinterInfo::defaultPrinter);    // PrintSupport
    L(QQmlEngine::objectOwnership); // Qml
    L(QQuickWindow::hasDefaultAlphaBuffer); // Quick
    L(new QQuickWidget());  // QuickWidgets
    L(QSqlDatabase::drivers);   // Sql
    L(QTest::currentTestFailed);    // Test
    L((new QUiLoader())->workingDirectory().Name);  // UiTools
    L(new QWebChannel());   // WebChannel
    L(QWebEngineUrlScheme::registerScheme); // WebEngine
    L(QWebEngineSettings::defaultSettings); // WebEngineWidgets
    L(QWebSocket::maxIncomingFrameSize);    // WebSockets
    L(QStyle::visualPos);

    return a.exec();
}
