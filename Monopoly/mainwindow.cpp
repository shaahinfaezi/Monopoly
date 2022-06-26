#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"
#include <vector>

using std::vector;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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
