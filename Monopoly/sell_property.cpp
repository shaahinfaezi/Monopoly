#include "sell_property.h"
#include "ui_sell_property.h"
#include "Property.h"
#include <QMessageBox>
#include <QDebug>




sell_property::sell_property(int Iterator,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sell_property)
{
    ui->setupUi(this);

    setWindowTitle("Sell Property");

    gameBoard=GameBoard::get_instance();

    this->Iterator=Iterator;
    ui->comboBox->clear();


    QPixmap pixmap(QString::fromStdString(gameBoard->Players.at(gameBoard->order)->MyProperties.at(Iterator)->get_PropertyCard()));

    ui->label_2->setPixmap(pixmap.scaled(422,574,Qt::KeepAspectRatio));

    ui->comboBox->clear();

    for(int i=0;i<int(gameBoard->Players.size());i++){

        if(gameBoard->Players.at(i)!=gameBoard->Players.at(gameBoard->order)){

        ui->comboBox->addItem(QString::fromStdString(gameBoard->Players.at(i)->get_nickname()));


}
    }

    ui->comboBox->setCurrentIndex(-1);



}

sell_property::~sell_property()
{
    delete ui;
}

void sell_property::on_pushButton_clicked()
{
    if(ui->comboBox->currentIndex()!=-1){

        if(!gameBoard->Empty_string_check(ui->lineEdit->text().toUtf8().constData()) && gameBoard->IsNumber(ui->lineEdit->text().toUtf8().constData()) &&ui->lineEdit->text().toInt()>0 ){

            QMessageBox::StandardButton reply;

             reply = QMessageBox::question(this, "Offer",ui->comboBox->currentText()+ " do you want to buy this property for "+ui->lineEdit->text() + " ?",

                                           QMessageBox::Yes|QMessageBox::No);


             if (reply == QMessageBox::Yes) {

                 int buyer=0;

                 for(int i=0;i<int(gameBoard->Players.size());i++){


                     if(QString::fromStdString(gameBoard->Players.at(i)->get_nickname())==ui->comboBox->currentText()){

                         buyer=i;
                     }

                 }





                 for(int i=0;i<int(gameBoard->Properties.size());i++){

                     if(gameBoard->Properties.at(i)==gameBoard->Players.at(gameBoard->order)->MyProperties.at(Iterator)){

                         gameBoard->Properties.at(i)->owner=gameBoard->Players.at(buyer);

                     }

                 }




                 gameBoard->Players.at(buyer)->MyProperties.push_back(gameBoard->Players.at(gameBoard->order)->MyProperties.at(Iterator));

                 gameBoard->Players.at(gameBoard->order)->MyProperties.erase(gameBoard->Players.at(gameBoard->order)->MyProperties.begin()+Iterator);


                 gameBoard->Players.at(buyer)->set_Munny(gameBoard->Players.at(buyer)->get_Munny()-ui->lineEdit->text().toInt());

                 gameBoard->Players.at(gameBoard->order)->set_Munny(gameBoard->Players.at(gameBoard->order)->get_Munny()+ui->lineEdit->text().toInt());

                 gameBoard->print_order();


                 QMessageBox::StandardButton reply=QMessageBox::information(this,"Information",ui->comboBox->currentText()+" bought this property from you.");

                 if(reply==QMessageBox::Ok || reply==QMessageBox::Close){


                     accept();


                 }

             }
             else {

                  QMessageBox::information(this,"Information",ui->comboBox->currentText()+" didn't accept your offer.");
             }


        }
        else{
             QMessageBox::warning(this,"Warning","Please enter a correct price.");

        }

    }
    else{

        QMessageBox::warning(this,"Warning","Please enter the player you want to send the offer.");
    }


}
