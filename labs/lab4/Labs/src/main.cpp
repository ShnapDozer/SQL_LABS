#include "include/MainWindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;

    qDebug("test");

    w.show();
    return a.exec();
}
