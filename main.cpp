#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "marker.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Marker marker;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("marker",&marker);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
