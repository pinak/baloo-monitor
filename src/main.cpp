#include <QGuiApplication>
#include <QtQml>
#include <QQmlApplicationEngine>

#include "monitor.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    BalooMonitor::Monitor mon;

    engine.rootContext()->setContextProperty("monitor", &mon);
    QString path = QStandardPaths::locate(QStandardPaths::DataLocation, "main.qml");
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
