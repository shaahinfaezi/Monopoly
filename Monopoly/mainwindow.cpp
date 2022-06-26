#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"
#include "QPixmap"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   QPixmap pic(":/res/Images/pic2.png");
   ui->labal2->setPixmap(pic.scaled(ui->labal2->width(),ui->labal2->height(),Qt::KeepAspectRatio));




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    int number_of_players=ui->comboBox->currentText().toInt();

    GameBoard * gameboard=GameBoard::get_instance(this,number_of_players);

    this->hide();

    gameboard->show();

}
