#include "my_properties.h"
#include "ui_my_properties.h"

my_Properties::my_Properties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::my_Properties)
{
    ui->setupUi(this);
}

my_Properties::~my_Properties()
{
    delete ui;
}
