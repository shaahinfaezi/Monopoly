#include "community_chance.h"
#include "ui_community_chance.h"




Community_Chance::Community_Chance(bool CommunityOrChance,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Community_Chance)
{
    ui->setupUi(this);

    gameboard=GameBoard::get_instance();




    if(CommunityOrChance){

        QPixmap card(QString::fromStdString(gameboard->CommunityCards.back()->get_path()));

        ui->label->setPixmap(card.scaled(344,200,Qt::KeepAspectRatio));


        setWindowTitle("Community Cards");



    }
    else{

        QPixmap card(QString::fromStdString(gameboard->ChanceCards.back()->get_path()));

        ui->label->setPixmap(card.scaled(344,200,Qt::KeepAspectRatio));


         setWindowTitle("Chance Cards");
    }



}

Community_Chance::~Community_Chance()
{
    delete ui;
}
