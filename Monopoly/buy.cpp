#include "buy.h"
#include "ui_buy.h"

Buy::Buy(Property* property,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Buy)
{
    ui->setupUi(this);

    this->property=property;

    QPixmap pixmap(QString::fromStdString(property->get_PropertyCard()));

   ui->label->setPixmap(pixmap.scaled(361,491,Qt::KeepAspectRatio));

}

Buy::~Buy()
{
    delete ui;
}
