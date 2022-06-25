#include "mainwindow.h"
#include "gameboard.h"
#include <QApplication>
#include <QDateTime>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
