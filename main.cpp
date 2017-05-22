#include "mainwindow.h"
#include <QApplication>
#include <QHash>
#include <QDebug>
#include "uhv2worker.h"

int main(int argc, char *argv[])
{

   QSerialPort *test = new QSerialPort();
   test->close();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
