#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "marker.h"
#include "imageprovider.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    auto ip=new ImageProvider;
    Marker marker(ip);
    engine.rootContext()->setContextProperty("marker",&marker);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.addImageProvider("image",ip);
    return app.exec();
}
