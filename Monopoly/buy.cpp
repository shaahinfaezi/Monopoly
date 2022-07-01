#include "buy.h"
#include "ui_buy.h"

Buy::Buy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Buy)
{
    ui->setupUi(this);
}

Buy::~Buy()
{
    delete ui;
}
