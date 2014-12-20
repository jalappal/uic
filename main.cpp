#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDeclarativeView>
#include <QtDebug>


#include "initdb.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSqlError err = initDb();

    qDebug() << err.text();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
