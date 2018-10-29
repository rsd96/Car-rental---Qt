#include "mainwindow.h"
#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //qDebug() << QDateTime::fromString("2017-12-20 18:59:31", "yyyy-MM-dd hh:mm:ss").toString("yyyy-MM-dd hh:mm:ss");

    return a.exec();
}
