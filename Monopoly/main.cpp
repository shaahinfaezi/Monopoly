#include "mainwindow.h"
#include "gameboard.h"
#include <QApplication>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon(":/res/Images/games.png"));
    MainWindow w;


    w.show();



    return a.exec();
}
