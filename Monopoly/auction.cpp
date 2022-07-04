#include "auction.h"
#include "ui_auction.h"
#include "Property.h"
#include <QMessageBox>


bool empty_string_check__(string s){

    if(all_of(s.begin(),s.end(),isspace)||s.empty()){
        return true;
    }
    else{
        return false;
    }

}

bool isNumber_(string s){

    QRegExp re("\\d*");
    if (re.exactMatch(QString::fromStdString(s)))
        return true;

    return false;


}

void auction::print(){

    ui->label_2->setText(QString::fromStdString(Bidders.at(iterator)->get_nickname()));

    ui->label_4->setText(QString::number(HighestBid)+"$");


    ui->lineEdit->clear();

}

auction::auction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auction)
{
    ui->setupUi(this);


    gameBoard=GameBoard::get_instance();

     property=gameBoard->Properties.at(gameBoard->Players.at(gameBoard->order)->get_position());

     QPixmap pixmap(QString::fromStdString(property->get_PropertyCard()));

    ui->label->setPixmap(pixmap.scaled(422,574,Qt::KeepAspectRatio));

    iterator=0;

    HighestBid=0;

    Bidders=gameBoard->Players;

    print();

    round=0;

}

auction::~auction()
{
    delete ui;
}

int  auction::BidderFinder(Player * Bidder){


    int index;

    for(int i=0;i<int(gameBoard->Players.size());++i){

        if(gameBoard->Players.at(i)->get_nickname()==Bidder->get_nickname()){

            index=i;

        }

    }


    return index;
}

void auction::on_pushButton_clicked()
{

    Bidders.erase(Bidders.begin()+iterator);

    if(iterator==int(Bidders.size()))
        iterator--;


    if(Bidders.size()==0){

        QMessageBox::StandardButton reply=QMessageBox::information(this,"information","No one wanted the property.");

        if(reply==QMessageBox::Ok || reply==QMessageBox::Close){

            accept();


        }




    }
    else{

        if(int(Bidders.size()==1) && HighestBid>0){


            int i=BidderFinder(Bidders.at(iterator));

           gameBoard->Players.at(i)->set_Munny(gameBoard->Players.at(i)->get_Munny()-HighestBid);

           gameBoard->Players.at(i)->MyProperties.push_back(property);

           property->owner=gameBoard->Players.at(i);

           QMessageBox::StandardButton reply=QMessageBox::information(this,"information","The property goes to "+QString::fromStdString(Bidders.at(iterator)->get_nickname())+ " for "+QString::number(HighestBid));

           if(reply==QMessageBox::Ok || reply==QMessageBox::Close){

               gameBoard->HideBuyButton();
               accept();



           }

        }
        else{



    print();
        }

    }



}

void auction::on_pushButton_2_clicked()
{

    if(!empty_string_check__(ui->lineEdit->text().toUtf8().constData()) && isNumber_(ui->lineEdit->text().toUtf8().constData()) &&ui->lineEdit->text().toInt()>0 ){

        int price=ui->lineEdit->text().toInt();

        if(price>HighestBid){

            HighestBid=price;

            HighestBidder=gameBoard->Players.at(BidderFinder(Bidders.at(iterator)));

        }


            iterator++;

            if(iterator==int(Bidders.size())){

                iterator=0;

                round++;

                if(round==5){


                    int i=BidderFinder(HighestBidder);

                   gameBoard->Players.at(i)->set_Munny(gameBoard->Players.at(i)->get_Munny()-HighestBid);

                   gameBoard->Players.at(i)->MyProperties.push_back(property);

                   property->owner=gameBoard->Players.at(i);

                   QMessageBox::StandardButton reply=QMessageBox::information(this,"information","The property goes to "+QString::fromStdString(HighestBidder->get_nickname())+ " for "+QString::number(HighestBid));

                   if(reply==QMessageBox::Ok || reply==QMessageBox::Close){

                       gameBoard->HideBuyButton();

                       accept();


                   }

                }
            }

            print();








    }
    else{



         QMessageBox::warning(this,"Warning","Please enter a correct price.");
    }
}
