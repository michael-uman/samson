#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "samson.h"
#include "appobject.h"


int qt_main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<appObject>("com.wunderbar.app", 1, 0, "MyApp");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}

int main(int argc, char * argv[]) {
    return keep_alive(qt_main, argc, argv);
}
