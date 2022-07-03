#include "buy.h"
#include "ui_buy.h"
#include <QMessageBox>
#include "auction.h"


Buy::Buy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Buy)
{
    ui->setupUi(this);

    gameboard=GameBoard::get_instance();

    this->property=gameboard->Properties.at(gameboard->Players.at(gameboard->order)->get_position());

    QPixmap pixmap(QString::fromStdString(property->get_PropertyCard()));

   ui->label->setPixmap(pixmap.scaled(321,471,Qt::KeepAspectRatio));

}

Buy::~Buy()
{
    delete ui;
}

void Buy::on_pushButton_clicked()
{

    int price=property->get_price();

   gameboard->Players.at(gameboard->order)->set_Munny(gameboard->Players.at(gameboard->order)->get_Munny()-price);

   gameboard->Players.at(gameboard->order)->MyProperties.push_back(property);

   property->owner=gameboard->Players.at(gameboard->order);


    QMessageBox::information(this,"Information","You've purchased this property");

    gameboard->print_order();

    gameboard->HideBuyButton();

    this->close();


}

void Buy::on_pushButton_2_clicked()
{

    auction * Auction=new auction(this);

    int code=Auction->exec();

    if(code==QDialog::Rejected ||code==QDialog::Accepted){

     this->close();

    }

}
