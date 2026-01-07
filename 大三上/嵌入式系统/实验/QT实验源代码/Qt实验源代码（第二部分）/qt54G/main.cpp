#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCursor>
#include "ec20.h"
#include "phonethread.h"
#include "workerobject.h"
#include <callrecordroles.h>
#include "lis3dhthread.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    CallRecordModel callRecordModel;

    QCursor cursor(Qt::BlankCursor);
    app.setOverrideCursor(cursor);

    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();
    MyBackend backend;
    bool isS5P6818 = false;
    PhoneThread *pthread = PhoneThread::instance();

    QThread workerThread;
    WorkerObject worker;

    worker.moveToThread(&workerThread);
    workerThread.start();

    qmlRegisterType<CallRecordModel>("CallRecordModel", 1, 0, "CallRecordModel");
    qmlRegisterType<EC20>("EC20", 1, 0, "EC20");
    qmlRegisterType<WorkerObject>("WorkerObject",1,0,"WorkerObject");
    context->setContextProperty("phoneThread", pthread);
//    qmlRegisterType<PhoneThread>("PhoneThread",1,0,"PhoneThread");
    qmlRegisterType<MyBackend>("MyBackend",1,0,"MyBackend");
#ifdef PLAT_S5P6818
    isS5P6818 = true;
    Lis3dhThread *lis3dhthread = Lis3dhThread::instance();
    context->setContextProperty("lis3dh", lis3dhthread);
#endif
    context->setContextProperty("isS5P6818", isS5P6818);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
