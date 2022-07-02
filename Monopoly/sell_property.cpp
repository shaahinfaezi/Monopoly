#include "sell_property.h"
#include "ui_sell_property.h"

sell_property::sell_property(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sell_property)
{
    ui->setupUi(this);
}

sell_property::~sell_property()
{
    delete ui;
}
