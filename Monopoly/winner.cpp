#include "winner.h"
#include "ui_winner.h"


Winner::Winner(string winnerName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Winner)
{
    ui->setupUi(this);

    setWindowTitle("Winner");

    QPixmap winner(":/res/Images/pngegg-removebg-preview.png");

    ui->label->setPixmap(winner.scaled(500,500,Qt::KeepAspectRatio));

    ui->label_2->setText("Congrats "+QString::fromStdString(winnerName)+",You WON!!!");


}

Winner::~Winner()
{
    delete ui;
}
