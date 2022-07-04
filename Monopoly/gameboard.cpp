#include "gameboard.h"
#include "ui_gameboard.h"
#include <QDebug>
#include "QPixmap"
#include <QScreen>
#include <QDebug>
#include <QPainter>
#include <QThread>
#include <QTimer>
#include "Property.h"
#include "buy.h"
#include <QMessageBox>
#include "my_properties.h"
#include "community_chance.h"
#include "mainwindow.h"

#include <stdlib.h>
#include <time.h>

#include "vector"


bool Empty_string_check(string s){

    if(all_of(s.begin(),s.end(),isspace)||s.empty()){
        return true;
    }
    else{
        return false;
    }

}

bool IsNumber(string s){

    QRegExp re("\\d*");
    if (re.exactMatch(QString::fromStdString(s)))
        return true;

    return false;


}

using std::vector;


template<class T>
void Randomizer(vector<T> &Variable){


      srand(time(NULL));

    for(int i=int(Variable.size())-1;i>0;i--){



      int j=rand() % (i+1);


      T temp=Variable.at(i);

      Variable.at(i)=Variable.at(j);

      Variable.at(j)=temp;


    }




}


void GameBoard::move(int destination){

    RenderMovement(destination);



    SituationCheck();
}

void GameBoard::BankruptCheck(){

qDebug()<<"check";


    if(Players.at(order)->get_Munny()<0){




        QMessageBox::information(this,"Information","Your balance is negative so we'll sell your houses and hotels to try to save you from bankruptcy.");


        int credit=0;

        for(int i=0;i<int(Players.at(order)->MyProperties.size());i++){

            if(Players.at(order)->MyProperties.at(i)->get_type()==PROPERTY){

                if(Players.at(order)->MyProperties.at(i)->get_number_of_houses()<5){

                    credit+=Players.at(order)->MyProperties.at(i)->get_number_of_houses()*Players.at(order)->MyProperties.at(i)->get_house()*0.5;

                }
                else{

                    credit+=Players.at(order)->MyProperties.at(i)->get_hotel()*0.5;

                }


            }



        }

        qDebug()<<credit;

        if(Players.at(order)->get_Munny()+credit<0){

          Bankrupt();



        }
        else{


            Players.at(order)->set_Munny(Players.at(order)->get_Munny()+credit);

            print_order();







        }















    }





}

void GameBoard::Bankrupt(){


     QMessageBox::information(this,"Information",QString::fromStdString(Players.at(order)->get_nickname())+" went bankrupt.");

    for(int i=0;i<int(Properties.size());i++){

        if(Properties.at(i)->owner==Players.at(order)){

            Properties.at(i)->owner=nullptr;

            Properties.at(i)->set_number_of_houses(0);

            Properties.at(i)->set_mortgage(false);

        }

    }

    int i;
    for(i=0;i<int(Properties.at(Players.at(order)->get_position())->PlayersOnProperty.size());i++){

        if(Properties.at(Players.at(order)->get_position())->PlayersOnProperty.at(i)->get_nickname()==Players.at(order)->get_nickname()){
            break;
        }

    }


    Properties.at(Players.at(order)->get_position())->PlayersOnProperty.at(i)->token->hide();

    Properties.at(Players.at(order)->get_position())->PlayersOnProperty.at(i)->token->setEnabled(false);

    Properties.at(Players.at(order)->get_position())->PlayersOnProperty.erase(Properties.at(Players.at(order)->get_position())->PlayersOnProperty.begin()+i);

    position=Players.at(order)->get_position();

    movement();

    number_of_players--;

    qDebug()<<order;

    Players.erase(Players.begin()+order);

    if(order==int(Players.size()))

        order=0;


     qDebug()<<order;


      BankruptCheck();

    if(Players.at(order)->number_of_turns_in_jail>-1){

        jail();

        Players.at(order)->number_of_turns_in_jail++;

    }
    else{



    print_order();

    ui->pushButton_2->setEnabled(true);

    ui->pushButton_2->show();


    ui->pushButton_3->hide();

    ui->pushButton_3->setEnabled(false);

    ui->pushButton->hide();

    ui->pushButton->setEnabled(false);

    ui->pushButton_5->hide();

    ui->pushButton_5->setEnabled(false);

    }

    if(Players.size()==1){





        QMessageBox::StandardButton reply=QMessageBox::information(this,"Information",QString::fromStdString(Players.at(order)->get_nickname())+" WON!!!!!!");

        if(reply==QMessageBox::Ok || reply==QMessageBox::Close){

            MainWindow * mainwindow=new MainWindow(this);

            mainwindow->show();

           this->hide();




        }

    }










}



GameBoard * GameBoard::instance=nullptr;

GameBoard::GameBoard(vector<string> nicknames,QWidget *parent,int number_of_players) :
    QDialog(parent),
    ui(new Ui::GameBoard),
    number_of_players(number_of_players)

{

    ui->setupUi(this);

    QScreen *screen = QGuiApplication::primaryScreen();
        QRect  screenGeometry = screen->geometry();
        int height = screenGeometry.height();
        int width = screenGeometry.width();

        this->setFixedSize(width,height);

        //showing the board

/////////////
    QPixmap pix=*new QPixmap(":/res/Images/pic5.png");

        QMatrix m;

        m.rotate(315);

        pix=pix.transformed(m);

        ui->logo->setPixmap(pix.scaled(ui->logo->width(),ui->logo->height(),Qt::KeepAspectRatio));


        QPixmap pix1=*new QPixmap(":/res/Images/bord/photo_2022-06-27_22-24-40.jpg");

            QMatrix m1;

            m1.rotate(135);

            pix1=pix1.transformed(m1);

            ui->logo2->setPixmap(pix1.scaled(ui->logo2->width(),ui->logo2->height(),Qt::KeepAspectRatio));

            QPixmap pix2=*new QPixmap(":/res/Images/bord/Chances161.jpg");

                QMatrix m2;

                m2.rotate(315);

                pix2=pix2.transformed(m2);

                ui->logo3->setPixmap(pix2.scaled(ui->logo2->width(),ui->logo2->height(),Qt::KeepAspectRatio));
                QPixmap pic(":/res/Images/photos/photo21.jpg");

                ui->label_2->setGeometry(ui->label_2->x(),ui->label_2->y(),80,131);

                ui->label_2->setPixmap(pic.scaled(ui->label_2->width(),ui->label_2->height(),Qt::KeepAspectRatio));

                qDebug()<<ui->label_2->width();



                QPixmap pic1(":/res/Images/photos/photo20.jpg");

                ui->label_3->setGeometry(ui->label_3->x(),ui->label_3->y(),80,131);

                ui->label_3->setPixmap(pic1.scaled(ui->label_3->width(),ui->label_3->height(),Qt::KeepAspectRatio));


                QPixmap pic2(":/res/Images/photos/photo19.jpg");

                ui->label_4->setGeometry(ui->label_4->x(),ui->label_4->y(),80,131);

                ui->label_4->setPixmap(pic2.scaled(ui->label_4->width(),ui->label_4->height(),Qt::KeepAspectRatio));


                QPixmap pic3(":/res/Images/photos/photo18.jpg");

                ui->label_5->setGeometry(ui->label_5->x(),ui->label_5->y(),80,131);

                ui->label_5->setPixmap(pic3.scaled(ui->label_5->width(),ui->label_5->height(),Qt::KeepAspectRatio));


                QPixmap pic4(":/res/Images/photos/photo1.jpg");

                ui->label_6->setGeometry(ui->label_6->x(),ui->label_6->y(),80,131);

                ui->label_6->setPixmap(pic4.scaled(ui->label_6->width(),ui->label_6->height(),Qt::KeepAspectRatio));


                QPixmap pic5(":/res/Images/photos/photo3.jpg");

                ui->label_7->setGeometry(ui->label_7->x(),ui->label_7->y(),80,131);

                ui->label_7->setPixmap(pic5.scaled(ui->label_7->width(),ui->label_7->height(),Qt::KeepAspectRatio));

                QPixmap pic6(":/res/Images/photos/photo13.jpg");

                ui->label_8->setGeometry(ui->label_8->x(),ui->label_8->y(),80,131);

                ui->label_8->setPixmap(pic6.scaled(ui->label_8->width(),ui->label_8->height(),Qt::KeepAspectRatio));



                QPixmap pic7(":/res/Images/photos/community chest2.png");

                ui->label_9->setGeometry(ui->label_9->x(),ui->label_9->y(),80,131);

                ui->label_9->setPixmap(pic7.scaled(ui->label_9->width(),ui->label_9->height(),Qt::KeepAspectRatio));



                QPixmap pic8(":/res/Images/photos/photo14.jpg");

                ui->label_10->setGeometry(ui->label_10->x(),ui->label_10->y(),80,131);

                ui->label_10->setPixmap(pic8.scaled(ui->label_10->width(),ui->label_10->height(),Qt::KeepAspectRatio));


              ///////////////////////////////////////////
                QPixmap pic9(":/res/Images/bord/photo_2022-06-27_21-51-45.jpg");

                ui->label_20->setGeometry(ui->label_20->x(),ui->label_20->y(),131,131);
                ui->label_20->setPixmap(pic9.scaled(ui->label_20->width(),ui->label_20->height(),Qt::KeepAspectRatio));

            ////////////////////////////////

                QPixmap pix3=*new QPixmap(":/res/Images/photos/photo28.jpg");

                    QMatrix m3;

                    m3.rotate(90);

                    pix3=pix3.transformed(m3);
                    ui->label_11->setGeometry(ui->label_11->x(),ui->label_11->y(),131,80);

                    ui->label_11->setPixmap(pix3.scaled(ui->label_11->width(),ui->label_11->height(),Qt::KeepAspectRatio));



                QPixmap pix4=*new QPixmap(":/res/Images/photos/photo27.jpg");

                     QMatrix m4;

                     m4.rotate(90);

                      pix4=pix4.transformed(m4);
                       ui->label_12->setGeometry(ui->label_12->x(),ui->label_12->y(),131,80) ;

                      ui->label_12->setPixmap(pix4.scaled(ui->label_12->width(),ui->label_12->height(),Qt::KeepAspectRatio));



                  QPixmap pix5=*new QPixmap(":/res/Images/photos/community chest2.png");

                      QMatrix m5;

                       m5.rotate(90);

                       pix5=pix5.transformed(m5);
                       ui->label_13->setGeometry(ui->label_13->x(),ui->label_13->y(),131,80);

                      ui->label_13->setPixmap(pix5.scaled(ui->label_13->width(),ui->label_13->height(),Qt::KeepAspectRatio));



                   QPixmap pix6=*new QPixmap(":/res/Images/photos/photo26.jpg");

                   QMatrix m6;

                    m6.rotate(90);

                    pix6=pix6.transformed(m6);
                    ui->label_14->setGeometry(ui->label_14->x(),ui->label_14->y(),131,80);

                     ui->label_14->setPixmap(pix6.scaled(ui->label_14->width(),ui->label_14->height(),Qt::KeepAspectRatio));




                    QPixmap pix7=*new QPixmap(":/res/Images/photos/photo5.jpg");

                    QMatrix m7;

                    m7.rotate(90);

                    pix7=pix7.transformed(m7);
                     ui->label_15->setGeometry(ui->label_15->x(),ui->label_15->y(),131,80);
                    ui->label_15->setPixmap(pix7.scaled(ui->label_15->width(),ui->label_15->height(),Qt::KeepAspectRatio));



                    QPixmap pix8=*new QPixmap(":/res/Images/photos/photo25.jpg");

                    QMatrix m8;

                    m8.rotate(90);

                    pix8=pix8.transformed(m8);
                    ui->label_16->setGeometry(ui->label_16->x(),ui->label_16->y(),131,80);
                    ui->label_16->setPixmap(pix8.scaled(ui->label_16->width(),ui->label_16->height(),Qt::KeepAspectRatio));


                    QPixmap pix9=*new QPixmap(":/res/Images/photos/photo24.jpg");

                    QMatrix m9;

                    m9.rotate(90);

                    pix9=pix9.transformed(m9);
                    ui->label_17->setGeometry(ui->label_17->x(),ui->label_17->y(),131,80);
                    ui->label_17->setPixmap(pix9.scaled(ui->label_17->width(),ui->label_17->height(),Qt::KeepAspectRatio));


                    QPixmap pix10=*new QPixmap(":/res/Images/photos/photo23.jpg");

                    QMatrix m10;

                    m10.rotate(90);

                    pix10=pix10.transformed(m10);
                      ui->label_18->setGeometry(ui->label_18->x(),ui->label_18->y(),131,80);
                    ui->label_18->setPixmap(pix10.scaled(ui->label_18->width(),ui->label_18->height(),Qt::KeepAspectRatio));


                    QPixmap pix11=*new QPixmap(":/res/Images/photos/photo22.jpg");

                    QMatrix m11;

                    m11.rotate(90);

                    pix11=pix11.transformed(m11);
                    ui->label_19->setGeometry(ui->label_19->x(),ui->label_19->y(),131,80);
                    ui->label_19->setPixmap(pix11.scaled(ui->label_19->width(),ui->label_19->height(),Qt::KeepAspectRatio));


///////////////////////////////////////
                     QPixmap pic10(":/res/Images/bord/photo_2022-06-27_21-51-42.jpg");
                    ui->label_21->setGeometry(ui->label_21->x(),ui->label_21->y(),131,131);
                    ui->label_21->setPixmap(pic10.scaled(ui->label_21->width(),ui->label_21->height(),Qt::KeepAspectRatio));



//////////////

                     QPixmap pix12=*new QPixmap(":/res/Images/photos/photo36.jpg");

                     QMatrix m12;

                     m12.rotate(180);

                     pix12=pix12.transformed(m12);
                     ui->label_23->setGeometry(ui->label_23->x(),ui->label_23->y(),80,131);
                     ui->label_23->setPixmap(pix12.scaled(ui->label_23->width(),ui->label_23->height(),Qt::KeepAspectRatio));



                     QPixmap pix13=*new QPixmap(":/res/Images/photos/photo39.jpg");

                     QMatrix m13;

                     m13.rotate(180);

                     pix13=pix13.transformed(m13);
                     ui->label_29->setGeometry(ui->label_29->x(),ui->label_29->y(),80,131);
                     ui->label_29->setPixmap(pix13.scaled(ui->label_29->width(),ui->label_29->height(),Qt::KeepAspectRatio));




                     QPixmap pix14=*new QPixmap(":/res/Images/photos/photo37.jpg");

                     QMatrix m14;

                     m14.rotate(180);

                     pix14=pix14.transformed(m14);
                     ui->label_30->setGeometry(ui->label_30->x(),ui->label_30->y(),80,131);
                     ui->label_30->setPixmap(pix14.scaled(ui->label_30->width(),ui->label_30->height(),Qt::KeepAspectRatio));




                     QPixmap pix15=*new QPixmap(":/res/Images/photos/photo38.jpg");

                     QMatrix m15;

                     m15.rotate(180);

                     pix15=pix15.transformed(m15);
                     ui->label_26->setGeometry(ui->label_26->x(),ui->label_26->y(),80,131);
                     ui->label_26->setPixmap(pix15.scaled(ui->label_26->width(),ui->label_26->height(),Qt::KeepAspectRatio));




                     QPixmap pix16=*new QPixmap(":/res/Images/photos/photo8.jpg");

                     QMatrix m16;

                     m16.rotate(180);

                     pix16=pix16.transformed(m16);
                     ui->label_27->setGeometry(ui->label_27->x(),ui->label_27->y(),80,131);
                     ui->label_27->setPixmap(pix16.scaled(ui->label_27->width(),ui->label_27->height(),Qt::KeepAspectRatio));




                     QPixmap pix17=*new QPixmap(":/res/Images/photos/photo29.jpg");

                     QMatrix m17;

                     m17.rotate(180);

                     pix17=pix17.transformed(m17);
                     ui->label_22->setGeometry(ui->label_22->x(),ui->label_22->y(),80,131);
                     ui->label_22->setPixmap(pix17.scaled(ui->label_22->width(),ui->label_22->height(),Qt::KeepAspectRatio));




                     QPixmap pix18=*new QPixmap(":/res/Images/photos/photo30.jpg");

                     QMatrix m18;

                     m18.rotate(180);

                     pix18=pix18.transformed(m18);
                     ui->label_24->setGeometry(ui->label_24->x(),ui->label_24->y(),80,131);
                     ui->label_24->setPixmap(pix18.scaled(ui->label_24->width(),ui->label_24->height(),Qt::KeepAspectRatio));





                     QPixmap pix19=*new QPixmap(":/res/Images/photos/photo31.jpg");

                     QMatrix m19;

                     m19.rotate(180);

                     pix19=pix19.transformed(m19);
                     ui->label_25->setGeometry(ui->label_25->x(),ui->label_25->y(),80,131);
                     ui->label_25->setPixmap(pix19.scaled(ui->label_25->width(),ui->label_25->height(),Qt::KeepAspectRatio));




                     QPixmap pix20=*new QPixmap(":/res/Images/photos/photo32.jpg");

                     QMatrix m20;

                     m20.rotate(180);

                     pix20=pix20.transformed(m20);
                     ui->label_28->setGeometry(ui->label_28->x(),ui->label_28->y(),80,131);
                     ui->label_28->setPixmap(pix20.scaled(ui->label_28->width(),ui->label_28->height(),Qt::KeepAspectRatio));

     //////////////////////////

                     QPixmap pix21=*new QPixmap(":/res/Images/photos/photo17.jpg");

                     QMatrix m21;

                     m21.rotate(270);

                     pix21=pix21.transformed(m21);
                     ui->label_38->setGeometry(ui->label_38->x(),ui->label_38->y(),131,80);
                     ui->label_38->setPixmap(pix21.scaled(ui->label_38->width(),ui->label_38->height(),Qt::KeepAspectRatio));


                     QPixmap pix22=*new QPixmap(":/res/Images/photos/photo16.jpg");

                     QMatrix m22;

                     m22.rotate(270);

                     pix22=pix22.transformed(m22);
                     ui->label_36->setGeometry(ui->label_36->x(),ui->label_36->y(),131,80);
                     ui->label_36->setPixmap(pix22.scaled(ui->label_36->width(),ui->label_36->height(),Qt::KeepAspectRatio));



                     QPixmap pix23=*new QPixmap(":/res/Images/photos/community chest2.png");

                     QMatrix m23;

                     m23.rotate(270);

                     pix23=pix23.transformed(m23);
                     ui->label_33->setGeometry(ui->label_33->x(),ui->label_33->y(),131,80);
                     ui->label_33->setPixmap(pix23.scaled(ui->label_33->width(),ui->label_33->height(),Qt::KeepAspectRatio));



                     QPixmap pix24=*new QPixmap(":/res/Images/photos/photo15.jpg");

                     QMatrix m24;

                     m24.rotate(270);

                     pix24=pix24.transformed(m24);
                     ui->label_35->setGeometry(ui->label_35->x(),ui->label_35->y(),131,80);
                     ui->label_35->setPixmap(pix24.scaled(ui->label_35->width(),ui->label_35->height(),Qt::KeepAspectRatio));



                     QPixmap pix25=*new QPixmap(":/res/Images/photos/photo11.jpg");

                     QMatrix m25;

                     m25.rotate(270);

                     pix25=pix25.transformed(m25);
                     ui->label_34->setGeometry(ui->label_34->x(),ui->label_34->y(),131,80);
                     ui->label_34->setPixmap(pix25.scaled(ui->label_34->width(),ui->label_34->height(),Qt::KeepAspectRatio));



                     QPixmap pix26=*new QPixmap(":/res/Images/photos/photo10.jpg");

                     QMatrix m26;

                     m26.rotate(270);

                     pix26=pix26.transformed(m26);
                     ui->label_31->setGeometry(ui->label_31->x(),ui->label_31->y(),131,80);
                     ui->label_31->setPixmap(pix26.scaled(ui->label_31->width(),ui->label_31->height(),Qt::KeepAspectRatio));



                     QPixmap pix27=*new QPixmap(":/res/Images/photos/photo33.jpg");

                     QMatrix m27;

                     m27.rotate(270);

                     pix27=pix27.transformed(m27);
                     ui->label_37->setGeometry(ui->label_37->x(),ui->label_37->y(),131,80);
                     ui->label_37->setPixmap(pix27.scaled(ui->label_37->width(),ui->label_37->height(),Qt::KeepAspectRatio));




                     QPixmap pix28=*new QPixmap(":/res/Images/photos/photo34.jpg");

                     QMatrix m28;

                     m28.rotate(270);

                     pix28=pix28.transformed(m28);
                     ui->label_32->setGeometry(ui->label_32->x(),ui->label_32->y(),131,80);
                     ui->label_32->setPixmap(pix28.scaled(ui->label_32->width(),ui->label_32->height(),Qt::KeepAspectRatio));



                     QPixmap pix29=*new QPixmap(":/res/Images/photos/photo35.jpg");

                     QMatrix m29;

                     m29.rotate(270);

                     pix29=pix29.transformed(m29);
                     ui->label_39->setGeometry(ui->label_39->x(),ui->label_39->y(),131,80);
                     ui->label_39->setPixmap(pix29.scaled(ui->label_39->width(),ui->label_39->height(),Qt::KeepAspectRatio));


//////////////////////
                     QPixmap pic11(":/res/Images/bord/go.png");
                     ui->label_40->setGeometry(ui->label_40->x(),ui->label_40->y(),131,131);
                     ui->label_40->setPixmap(pic11.scaled(ui->label_40->width(),ui->label_40->height(),Qt::KeepAspectRatio));

/////////////////////////
                     QPixmap pix30=*new QPixmap(":/res/Images/bord/photo_2022-06-27_21-51-35.jpg");

                     QMatrix m30;

                     m30.rotate(270);

                     pix30=pix30.transformed(m30);

                      ui->label_41->setGeometry(ui->label_41->x(),ui->label_41->y(),131,131);
                      ui->label_41->setPixmap(pix30.scaled(ui->label_41->width(),ui->label_41->height(),Qt::KeepAspectRatio));






//vared kardane path va function kart haye shans






    Chance *tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Advance_To_Boardwalk 1.png");

    tempChance->set_function(BOARDWALK);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Advance_To_Go 2.png");

    tempChance->set_function(GO);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_ATIA3.png");

    tempChance->set_function(ILLINOIS);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_ATSCP 4.png");

    tempChance->set_function(ST_CHARLES_GO);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_ATTNR5.png");

    tempChance->set_function( RAILROAD);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_ATTNU6.png");

    tempChance->set_function(UTILIY);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_BPYD7.png");

    tempChance->set_function(DIVIDEND);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_GB3S8.png");

    tempChance->set_function(THREE_SPACES);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_GOOJF9.png");

    tempChance->set_function(GETOUT);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_GTJ10.png");

    tempChance->set_function(JAIL_NO_GO);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_MGR11.png");

    tempChance->set_function(REPAIRS);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_PPT12.png");

    tempChance->set_function(POORTAX);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_TAROTR13.png");

    tempChance->set_function(READING_GO);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_YBALM14.png");

    tempChance->set_function(ONE_FIFTY);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_YHBAECOTB15.jpg");

    tempChance->set_function(FIFTY_FOR_EVERYONE);

    ChanceCards.push_back(tempChance);

    //

    tempChance=new Chance();

    tempChance->set_path(":/res/Images/chance/Chance_ATTNR5.png");

    tempChance->set_function(RAILROAD2);

    ChanceCards.push_back(tempChance);

    //////////////////////////////////////////



    Community * tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/CC_Advance_to_Go1.png");

    tempCommunity->set_function(GO_);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_BEIYF4.png");

    tempCommunity->set_function(BANK200);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_DF11.png");

    tempCommunity->set_function(DOCTOR50);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_FSOS5.png");

    tempCommunity->set_function(STOCK45);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_GOO10.png");

    tempCommunity->set_function(FIFTY_FROM_EVERYONE);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_GOOJF16.png");

    tempCommunity->set_function(GETOUT_);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_GTJ15.png");

    tempCommunity->set_function(JAIL_NO_GO_);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_ITR6.png");

    tempCommunity->set_function(TAX20);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_LIM2.png");

    tempCommunity->set_function(INSURANCE100);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_PH12.png");

    tempCommunity->set_function(HOSPITAL100);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_PST13.png");

    tempCommunity->set_function(SCHOOL150);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_RFS7.png");

    tempCommunity->set_function(SERVICE25);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_XFM9.png");

    tempCommunity->set_function(XMAS100);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_YAAFSR14.png");

    tempCommunity->set_function(REPAIRS_);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_YHWSPIABC3.png");

    tempCommunity->set_function(BEAUTY20);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_YI8.png");

    tempCommunity->set_function(INHERIT100);

    CommunityCards.push_back(tempCommunity);



    /////////////////////////////////////////////

    Randomizer(ChanceCards);

    Randomizer(CommunityCards);





        tokens_path.push_back(":/res/Images/mohre/monopoly-battleship-piece-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/monopoly-boot-piece-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/monopoly-cat-piece-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/monopoly-thimble-piece-retired-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/monopoly-top-hat__1_-removebg-preview (1).png");

        tokens_path.push_back(":/res/Images/mohre/monopoly-wheelbarrow-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/race-car-piece-monopoly-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/scottie-dog-monopoly-piece-removebg-preview.png");

        //khane haye board
        vector<QLabel*> Board;

          Board.push_back(ui->label_40);
          Board.push_back(ui->label_10);
          Board.push_back(ui->label_9);
          Board.push_back(ui->label_8);
          Board.push_back(ui->label_7);
          Board.push_back(ui->label_6);
          Board.push_back(ui->label_5);
          Board.push_back(ui->label_4);
          Board.push_back(ui->label_3);
          Board.push_back(ui->label_2);
          Board.push_back(ui->label_20);
          Board.push_back(ui->label_19);
          Board.push_back(ui->label_18);
          Board.push_back(ui->label_17);
          Board.push_back(ui->label_16);
          Board.push_back(ui->label_15);
          Board.push_back(ui->label_14);
          Board.push_back(ui->label_13);
          Board.push_back(ui->label_12);
          Board.push_back(ui->label_11);
          Board.push_back(ui->label_21);
          Board.push_back(ui->label_23);
          Board.push_back(ui->label_29);
          Board.push_back(ui->label_30);
          Board.push_back(ui->label_26);
          Board.push_back(ui->label_27);
          Board.push_back(ui->label_22);
          Board.push_back(ui->label_24);
          Board.push_back(ui->label_25);
          Board.push_back(ui->label_28);
          Board.push_back(ui->label_41);
          Board.push_back(ui->label_38);
          Board.push_back(ui->label_36);
          Board.push_back(ui->label_33);
          Board.push_back(ui->label_35);
          Board.push_back(ui->label_34);
          Board.push_back(ui->label_31);
          Board.push_back(ui->label_37);
          Board.push_back(ui->label_32);
          Board.push_back(ui->label_39);

         //sanad haye malekiat



          Property * tempGo=new Property(Board.at(0),GO__);

          Property * tempP=new Property(Board.at(1),PROPERTY,":/res/Images/Properties/1.png",60,2,10,30,90,160,250,30,50,50,"purple");

          Property * tempChest1=new Property(Board.at(2),COMMUNITY);

          Property * tempP1=new Property(Board.at(3),PROPERTY,":/res/Images/Properties/2.png",60,4,20,60,180,320,450,30,50,50,"purple");

          Property * tempIncomeTax=new Property(Board.at(4),INCOMETAX);

          Property * tempRR1=new Property(Board.at(5),RR,":/res/Images/Properties/23.png",200,25,50,100,200,100,"black");

          Property * tempP2=new Property(Board.at(6),PROPERTY,":/res/Images/Properties/3.png",100,6,30,90,270,400,550,50,50,50,"light blue");

          Property * tempChance1=new Property(Board.at(7),CHANCE);

          Property * tempP3=new Property(Board.at(8),PROPERTY,":/res/Images/Properties/4.png",100,6,30,90,270,400,550,50,50,50,"light blue");

          Property * tempP4=new Property(Board.at(9),PROPERTY,":/res/Images/Properties/5.png",120,8,40,100,300,450,600,60,50,50,"light blue");

          Property * tempJail=new Property(Board.at(10),JAIL);

          Property * tempP5=new Property(Board.at(11),PROPERTY,":/res/Images/Properties/6.png",140,10,50,150,450,625,750,70,100,100,"pink");

          Property * tempElectric=new Property(Board.at(12),UTILITY_,":/res/Images/Properties/photo_2022-06-28_19-00-13.jpg",150,4,10,75,"white");

          Property * tempP6=new Property(Board.at(13),PROPERTY,":/res/Images/Properties/7.png",140,10,50,150,450,625,750,70,100,100,"pink");

          Property * tempP7=new Property(Board.at(14),PROPERTY,":/res/Images/Properties/8.png",160,12,60,180,500,700,900,80,100,100,"pink");

          Property * tempRR2=new Property(Board.at(15),RR,":/res/Images/Properties/24.png",200,25,50,100,200,100,"black");

          Property * tempP8=new Property(Board.at(16),PROPERTY,":/res/Images/Properties/9.png",180,14,70,200,550,750,950,90,100,100,"orange");

          Property * tempChest2=new Property(Board.at(17),COMMUNITY);

          Property * tempP9=new Property(Board.at(18),PROPERTY,":/res/Images/Properties/10.png",180,14,70,200,550,750,950,90,100,100,"orange");

          Property * tempP10=new Property(Board.at(19),PROPERTY,":/res/Images/Properties/11.png",200,16,80,220,600,800,1000,100,100,100,"orange");

          Property * tempParking=new Property(Board.at(20),PARKING);

          Property * tempP11=new Property(Board.at(21),PROPERTY,":/res/Images/Properties/12.png",220,18,90,250,700,875,1050,110,150,150,"red");

          Property * tempChance2=new Property(Board.at(22),CHANCE);

          Property * tempP12=new Property(Board.at(23),PROPERTY,":/res/Images/Properties/13.png",220,18,90,250,700,875,1050,110,150,150,"red");

          Property * tempP13=new Property(Board.at(24),PROPERTY,":/res/Images/Properties/14.png",240,20,100,300,750,925,1100,120,150,150,"red");

          Property * tempRR3=new Property(Board.at(25),RR,":/res/Images/Properties/25.png",200,25,50,100,200,100,"black");

          Property * tempP14=new Property(Board.at(26),PROPERTY,":/res/Images/Properties/15.png",260,22,110,330,800,975,1150,130,150,150,"yellow");

          Property * tempP15=new Property(Board.at(27),PROPERTY,":/res/Images/Properties/16.png",260,22,110,330,800,975,1150,130,150,150,"yellow");

          Property * tempWater=new Property(Board.at(28),UTILITY_,":/res/Images/Properties/photo_2022-06-28_19-00-16.jpg",150,4,10,75,"white");

          Property * tempP16=new Property(Board.at(29),PROPERTY,":/res/Images/Properties/17.png",280,24,120,360,850,1025,1200,140,150,150,"yellow");

          Property * tempGOTOJAIL=new Property(Board.at(30),GOTOJAIL);

          Property * tempP17=new Property(Board.at(31),PROPERTY,":/res/Images/Properties/18.png",300,26,130,390,900,1100,1275,150,200,200,"green");

          Property * tempP18=new Property(Board.at(32),PROPERTY,":/res/Images/Properties/19.png",300,26,130,390,900,1100,1275,150,200,200,"green");

          Property * tempChest3=new Property(Board.at(33),COMMUNITY);

          Property * tempP19=new Property(Board.at(34),PROPERTY,":/res/Images/Properties/20.png",320,28,150,450,1000,1200,1400,160,200,200,"green");

          Property * tempRR4=new Property(Board.at(35),RR,":/res/Images/Properties/26.png",200,25,50,100,200,100,"black");

          Property * tempChance3=new Property(Board.at(36),CHANCE);

          Property * tempP20=new Property(Board.at(37),PROPERTY,":/res/Images/Properties/21.png",350,35,175,500,1100,1300,1500,175,200,200,"blue");

          Property * tempLuxuryTax=new Property(Board.at(38),LUXURYTAX);

          Property * tempP21=new Property(Board.at(39),PROPERTY,":/res/Images/Properties/22.png",400,50,200,600,1400,1700,2000,200,200,200,"blue");


          Properties.push_back(tempGo);

          Properties.push_back(tempP);

          Properties.push_back(tempChest1);

          Properties.push_back(tempP1);

          Properties.push_back(tempIncomeTax);

          Properties.push_back(tempRR1);

          Properties.push_back(tempP2);

          Properties.push_back(tempChance1);

          Properties.push_back(tempP3);

          Properties.push_back(tempP4);

          Properties.push_back(tempJail);

          Properties.push_back(tempP5);

          Properties.push_back(tempElectric);

          Properties.push_back(tempP6);

          Properties.push_back(tempP7);

          Properties.push_back(tempRR2);

          Properties.push_back(tempP8);

          Properties.push_back(tempChest2);

          Properties.push_back(tempP9);

          Properties.push_back(tempP10);

          Properties.push_back(tempParking);

          Properties.push_back(tempP11);

          Properties.push_back(tempChance2);

          Properties.push_back(tempP12);

          Properties.push_back(tempP13);

          Properties.push_back(tempRR3);

          Properties.push_back(tempP14);

          Properties.push_back(tempP15);

          Properties.push_back(tempWater);

          Properties.push_back(tempP16);

          Properties.push_back(tempGOTOJAIL);

          Properties.push_back(tempP17);

          Properties.push_back(tempP18);

          Properties.push_back(tempChest3);

          Properties.push_back(tempP19);

          Properties.push_back(tempRR4);

          Properties.push_back(tempChance3);

          Properties.push_back(tempP20);

          Properties.push_back(tempLuxuryTax);

          Properties.push_back(tempP21);




    Randomizer(tokens_path);

    vector<QLabel*> AllOfTheTokenLabels;

    AllOfTheTokenLabels.push_back(ui->label_47);

    AllOfTheTokenLabels.push_back(ui->label_48);

    AllOfTheTokenLabels.push_back(ui->label_49);

    AllOfTheTokenLabels.push_back(ui->label_50);

    AllOfTheTokenLabels.push_back(ui->label_51);

    AllOfTheTokenLabels.push_back(ui->label_52);

    AllOfTheTokenLabels.push_back(ui->label_53);

    AllOfTheTokenLabels.push_back(ui->label_54);

    vector<QLabel*> tokens;

    for(int i=0;i<int(AllOfTheTokenLabels.size());i++){


    QPixmap *pixmap=new QPixmap(QString::fromStdString(tokens_path.at(i)));

    AllOfTheTokenLabels.at(i)->setPixmap(pixmap->scaled(150,150,Qt::KeepAspectRatio));

    tokens.push_back(AllOfTheTokenLabels.at(i));


}



    for(int i=0;i<8;i++){
        tokens.at(i)->hide();
        tokens.at(i)->setEnabled(false);
    }


    for(int i=0;i<number_of_players;i++){



        //sakhtane Player * va dadan be vector



        Player* tempPlayer=new Player(nicknames.at(i),tokens.at(i));
        Players.push_back(tempPlayer);

        Players.at(i)->tokenPath=tokens_path.at(i);

    }


    Randomizer(Players);



    srand(time(NULL));

    Dice_path.push_back(":/res/Images/Dice/1.png");

    Dice_path.push_back(":/res/Images/Dice/2.png");

    Dice_path.push_back(":/res/Images/Dice/3.png");

    Dice_path.push_back(":/res/Images/Dice/4.png");

    Dice_path.push_back(":/res/Images/Dice/5.png");

    Dice_path.push_back(":/res/Images/Dice/6.png");

    ui->pushButton->hide();

    ui->pushButton_2->hide();

    ui->pushButton_3->hide();

    ui->pushButton->setEnabled(false);

    ui->pushButton_2->setEnabled(false);

    ui->pushButton_3->setEnabled(false);

    ui->pushButton_5->hide();

    ui->pushButton_5->setEnabled(false);

    ui->label_43->hide();

    ui->label_43->setEnabled(false);

    ui->label_44->hide();

    ui->label_44->setEnabled(false);




        order=0;

        print_order();

        Double=0;

        ui->pushButton_6->hide();

        ui->pushButton_6->setEnabled(false);

        ui->pushButton_7->hide();

        ui->pushButton_7->setEnabled(false);

        ui->pushButton_8->hide();

        ui->pushButton_8->setEnabled(false);

        ui->pushButton_9->hide();

        ui->pushButton_9->setEnabled(false);

        ChanceToUtility=false;

        ui->label_57->hide();

       ui->label_57->setEnabled(false);

        ui->label_58->hide();

        ui->label_58->setEnabled(false);

        ui->label_59->hide();

        ui->label_59->setEnabled(false);

        ui->pushButton_10->hide();

        ui->pushButton_10->setEnabled(false);

        ui->pushButton_11->hide();

        ui->pushButton_11->setEnabled(false);

        ui->comboBox->hide();

        ui->comboBox->setEnabled(false);

        ui->lineEdit->hide();

        ui->lineEdit->setEnabled(false);


}
bool GameBoard::throwDice(int &Dice1,int &Dice2){



    Dice1=rand() % 6 + 1;

    Dice2=rand() % 6 + 1;

    if(Dice1==Dice2){
        return true;

    }
    else{
        return false;

    }

}

void GameBoard::printDice(int Dice1,int Dice2){

    ui->label_45->show();
    ui->label_46->show();
    ui->label_55->show();

    ui->label_45->setEnabled(true);
    ui->label_46->setEnabled(true);
    ui->label_55->setEnabled(true);



    QPixmap dice1(QString::fromStdString(Dice_path.at(Dice1-1)));

    ui->label_45->setPixmap(dice1.scaled(ui->label_46->width(),ui->label_46->height(),Qt::KeepAspectRatio));

    QPixmap dice2(QString::fromStdString(Dice_path.at(Dice2-1)));

    ui->label_46->setPixmap(dice2.scaled(ui->label_46->width(),ui->label_46->height(),Qt::KeepAspectRatio));


    ui->label_55->setText(QString::fromStdString(Players.at(order)->get_nickname())+"'s sum is : "+QString::number(Dice1+Dice2));

}



void GameBoard::print_order(){


    ui->label_42->setText(QString::fromStdString(Players.at(order)->get_nickname()));

    ui->label_44->setText(QString::number(Players.at(order)->get_Munny())+"$");

    if(Players.at(order)->get_jail()==true){

        QPixmap JailCard(":/res/Images/download__7_-removebg-preview.png");

        ui->label_57->setPixmap(JailCard.scaled(274,184,Qt::KeepAspectRatio));

        ui->label_57->show();

        ui->label_57->setEnabled(true);

        ui->pushButton_10->show();

        ui->pushButton_10->setEnabled(true);



        ui->label_58->hide();

        ui->label_58->setEnabled(false);

        ui->label_59->hide();

        ui->label_59->setEnabled(false);

        ui->pushButton_11->hide();

        ui->pushButton_11->setEnabled(false);

        ui->comboBox->hide();

        ui->comboBox->setEnabled(false);

        ui->lineEdit->hide();

        ui->lineEdit->setEnabled(false);

    }

    else{

        ui->label_57->hide();

        ui->label_57->setEnabled(false);

        ui->label_58->hide();

        ui->label_58->setEnabled(false);

        ui->label_59->hide();

        ui->label_59->setEnabled(false);

        ui->pushButton_10->hide();

        ui->pushButton_10->setEnabled(false);

        ui->pushButton_11->hide();

        ui->pushButton_11->setEnabled(false);

        ui->comboBox->hide();

        ui->comboBox->setEnabled(false);

        ui->lineEdit->hide();

        ui->lineEdit->setEnabled(false);

        ui->pushButton_8->hide();

        ui->pushButton_8->setEnabled(false);


    }


}

//singleton pattern
GameBoard * GameBoard::get_instance(vector<string> nicknames,QWidget *parent,int number_of_players){

    if(instance==nullptr){

        instance=new GameBoard(nicknames,parent,number_of_players);


    }

     return instance;




}

GameBoard::~GameBoard()
{
    delete ui;


}

void GameBoard::on_pushButton_4_clicked()
{

    throwDice(Dice1,Dice2);

    printDice(Dice1,Dice2);

    sums[order]=Dice1+Dice2;

    if(order<number_of_players-1){

        order++;



        print_order();


    }
    else{


        for(int i=0;i<number_of_players;i++){

            for(int j=0;j<number_of_players-i-1;j++){

                if(sums[j+1]>sums[j]){


                    int temp=sums[j+1];

                    sums[j+1]=sums[j];

                    sums[j]=temp;

                    Player * tempPlayer=Players.at(j+1);

                    Players.at(j+1)=Players.at(j);

                    Players.at(j)=tempPlayer;



                }
            }


        }
        order=0;

        ui->pushButton_4->hide();

        ui->pushButton_4->setEnabled(false);

        ui->pushButton->show();

        ui->pushButton->setEnabled(true);

        ui->pushButton_2->show();

        ui->pushButton_2->setEnabled(true);

        ui->pushButton_3->show();

        ui->pushButton_3->setEnabled(true);

        ui->label_44->show();

        ui->label_44->setEnabled(true);

        for(int i=0;i<number_of_players;i++){

            Players.at(i)->token->show();

            Players.at(i)->token->setEnabled(true);

        }


        for(int i=0;i<number_of_players;i++){

            Properties.at(0)->PlayersOnProperty.push_back(Players.at(i));

            Players.at(i)->set_position(0);

        }

       position=0;


       movement();

       print_order();

       ui->pushButton_3->hide();

       ui->pushButton_3->setEnabled(false);

       ui->pushButton->hide();

       ui->pushButton->setEnabled(false);

       ui->pushButton_5->hide();

       ui->pushButton_5->setEnabled(false);



    }



}

void GameBoard::movement(){

    int number_of_players_in_position=int(Properties.at(position)->PlayersOnProperty.size());

    int x=Properties.at(position)->PropertyOnTheBoard->x();

    int y=Properties.at(position)->PropertyOnTheBoard->y();

    int width=Properties.at(position)->PropertyOnTheBoard->width();

    int height=Properties.at(position)->PropertyOnTheBoard->height();

    int Tokenx=0;

    int Tokeny=0;

    int Tokenwidth=0;

    int Tokenheight=0;

//radif 1
if(position<10){
    if(number_of_players_in_position<5){

        if(position==0){
            Tokenx=x-0.70*width+(number_of_players_in_position*width/7);
        }
        else{
             Tokenx=x-0.46*width;
        }


        Tokeny=y;
    }

    else{
        Tokenx=x+0.0001*width-5;

        Tokeny=1.01*y;
    }

}
//radif 2
else if(position<=19){

    if(number_of_players_in_position<5){


        Tokenx=x+0.4*width;

        Tokeny=y-0.6*height;
    }

    else{

        if(position==10){

            Tokeny=y-0.0001*height-75;

        }
        else{

            Tokeny=y-0.0001*height-35;

        }

        Tokenx=1.01*(x+0.6*width);


    }



}

//radif 3
else if(position<=29){


    if(number_of_players_in_position<5){

        if(position==20 && number_of_players_in_position==1){



               Tokenx=x-0.3*width;


        }

        if(position==20){
            Tokenx=x-0.70*width+(number_of_players_in_position*width/7);
        }
        else{
             Tokenx=x-0.46*width;
        }


        if(number_of_players_in_position<3){

            Tokeny=y+0.2*height;

        }
        else{
           Tokeny=y+0.45*height;
        }


    }

    else{



        Tokenx=x+0.0001*width-7.5;

        Tokeny=0.99*y+0.65*height;
    }



}
//radif 4
else if(position<=39){

    if(number_of_players_in_position<5){

        Tokenx=x+0.1*width;

         Tokeny=y-0.5*height;
    }

    else{
        Tokenx=1.01*(x+0.05*width);

        if(position==30){

            Tokeny=y-0.0001*height-75;

        }
        else{

            Tokeny=y-0.0001*height-35;

        }
    }


}



    for(int i=0;i<number_of_players_in_position;i++){





    //radif 1
    if(position<10){

        if(number_of_players_in_position%2!=0 && i==number_of_players_in_position-1){

            Tokenwidth=1.6*width;

        }
        else{


            Tokenwidth=1.54*width;

        }

        int column=0.5*(number_of_players_in_position+1);

        int useableHeight=height-(column+1)*(height*0.1);


        Tokenheight=1.42*(useableHeight/column);



        QPixmap *temp=new QPixmap(QString::fromStdString(Properties.at(position)->PlayersOnProperty.at(i)->tokenPath));


        Properties.at(position)->PlayersOnProperty.at(i)->token->setPixmap(temp->scaled(Tokenwidth,Tokenheight,Qt::KeepAspectRatio));


        Properties.at(position)->PlayersOnProperty.at(i)->token->setGeometry(Tokenx,Tokeny,Tokenwidth,Tokenheight);




        if(i%2!=0){

            if(number_of_players_in_position<5){


                if(position==0){
                    Tokenx=x-0.70*width+(number_of_players_in_position*width/7);
                }
                else{
                     Tokenx=x-0.46*width;
                }


            }

            else{
                Tokenx=x+0.0001*width-5;
            }

            Tokeny+=(0.03*height)+Tokenheight;
        }
        else{

            Tokenx+=0.5*width;



        }



    }
    //radif 2
    else if(position<=19){



        if(number_of_players_in_position%2!=0 && i==number_of_players_in_position-1){

            Tokenheight=1.6*height;

        }
        else{

            Tokenheight=1.54*height;

        }

        int column=0.5*(number_of_players_in_position+1);

        int useableWidth=width-(column+1)*(width*0.1);


        Tokenwidth=1.42*(useableWidth/column);


        QPixmap temp=*new QPixmap(QString::fromStdString(Properties.at(position)->PlayersOnProperty.at(i)->tokenPath));

        QMatrix m;

        m.rotate(90);

        temp=temp.transformed(m);

        Properties.at(position)->PlayersOnProperty.at(i)->token->setPixmap(temp.scaled(Tokenwidth,Tokenheight,Qt::KeepAspectRatio));

        Properties.at(position)->PlayersOnProperty.at(i)->token->setGeometry(Tokenx,Tokeny,Tokenwidth,Tokenheight);


        if(i%2!=0){




                if(number_of_players_in_position<5){

                    Tokeny=y-0.6*height;
                }

                else{



                    if(position==10){

                        Tokeny=y-0.0001*height-75;

                    }
                    else{

                        Tokeny=y-0.0001*height-35;

                    }



                }


            Tokenx-=(0.01*width)+0.8*Tokenwidth;
        }
        else{



                Tokeny+=0.5*height;



        }

    }
    //radif 3
    else if(position<=29){

        if(number_of_players_in_position%2!=0 && i==number_of_players_in_position-1){

            Tokenwidth=1.6*width;

        }
        else{


            Tokenwidth=1.54*width;

        }

        int column=0.5*(number_of_players_in_position+1);

        int useableHeight=height-(column+1)*(height*0.1);


        Tokenheight=1.42*(useableHeight/column);


          if(position==20 && number_of_players_in_position==1){

            Tokenwidth=1.3*width;

            Tokenheight=1.3*height;
          }

        QPixmap temp=*new QPixmap(QString::fromStdString(Properties.at(position)->PlayersOnProperty.at(i)->tokenPath));

        QMatrix m;

        m.rotate(540);

        temp=temp.transformed(m);


        Properties.at(position)->PlayersOnProperty.at(i)->token->setPixmap(temp.scaled(Tokenwidth,Tokenheight,Qt::KeepAspectRatio));


        Properties.at(position)->PlayersOnProperty.at(i)->token->setGeometry(Tokenx,Tokeny,Tokenwidth,Tokenheight);

        if(i%2!=0){

            if(number_of_players_in_position<5){


                if(position==20){

                    Tokenx=x-0.70*width+(number_of_players_in_position*width/7);

                }
                else{
                     Tokenx=x-0.46*width;
                }




            }

            else{
                Tokenx=x+0.0001*width-7.5;


            }

            Tokeny-=(0.03*height)+Tokenheight;
        }
        else{

            Tokenx+=0.5*width;



        }





    }
    //radif 4
    else if(position<=39){


        if(number_of_players_in_position%2!=0 && i==number_of_players_in_position-1){

            Tokenheight=1.6*height;

        }
        else{

            Tokenheight=1.54*height;

        }

        int column=0.5*(number_of_players_in_position+1);

        int useableWidth=width-(column+1)*(width*0.1);


        Tokenwidth=1.42*(useableWidth/column);


        QPixmap temp=*new QPixmap(QString::fromStdString(Properties.at(position)->PlayersOnProperty.at(i)->tokenPath));

        QMatrix m;

        m.rotate(270);

        temp=temp.transformed(m);

        Properties.at(position)->PlayersOnProperty.at(i)->token->setPixmap(temp.scaled(Tokenwidth,Tokenheight,Qt::KeepAspectRatio));

        Properties.at(position)->PlayersOnProperty.at(i)->token->setGeometry(Tokenx,Tokeny,Tokenwidth,Tokenheight);


        if(i%2!=0){



            if(number_of_players_in_position<5){


                   Tokeny=y-0.5*height;
               }

               else{


                if(position==30){

                    Tokeny=y-0.0001*height-75;

                }
                else{

                    Tokeny=y-0.0001*height-35;

                }

               }

            Tokenx+=(0.01*width)+Tokenwidth;
        }
        else{



                Tokeny+=0.5*height;



        }



    }








    }



}

void GameBoard::clearDice(){

    ui->label_45->hide();
    ui->label_46->hide();
    ui->label_55->hide();

    ui->label_45->setEnabled(false);
    ui->label_46->setEnabled(false);
    ui->label_55->setEnabled(false);


}

void GameBoard::PassGo(){
    if(position>39){

        position=position%40;

        Players.at(order)->set_position(position);

        Players.at(order)->set_Munny(Players.at(order)->get_Munny()+200);

        print_order();
    }
}

void GameBoard::set_position(int desination){



    Players.at(order)->set_position(desination);


    position=Players.at(order)->get_position();


    PassGo();

}

void GameBoard::RenderMovement(int destination){

    int tempPos=Players.at(order)->get_position();


    int i;
    for(i=0;i<int(Properties.at(tempPos)->PlayersOnProperty.size());i++){

        if(Properties.at(tempPos)->PlayersOnProperty.at(i)->get_nickname()==Players.at(order)->get_nickname()){
            break;
        }

    }




    Properties.at(tempPos)->PlayersOnProperty.erase(Properties.at(tempPos)->PlayersOnProperty.begin()+i);


    set_position(destination);

     Properties.at(position)->PlayersOnProperty.push_back(Players.at(order));

    movement();

    position=tempPos;

    movement();





}

bool GameBoard::Monopoly(string color,Player* Owner){

    for(int i=0;i<int(Properties.size());i++){

        if(Properties.at(i)->get_color()==color){

            if(Properties.at(i)->owner==nullptr){
                return false;
            }

            if(Properties.at(i)->owner!=Owner){
                return false;
            }

        }

    }

    return true;

}

void GameBoard::jail(){

    print_order();

    ui->pushButton->hide();

    ui->pushButton->setEnabled(false);

    ui->pushButton_3->hide();

    ui->pushButton_3->setEnabled(false);

    ui->pushButton_5->hide();

    ui->pushButton_5->setEnabled(false);

    ui->pushButton_6->show();

    ui->pushButton_6->setEnabled(true);

    ui->pushButton_7->show();

    ui->pushButton_7->setEnabled(true);

    if(Players.at(order)->get_jail()){

        ui->pushButton_8->show();

        ui->pushButton_8->setEnabled(true);

    }



}

void GameBoard::SituationCheck(){


    Property * tempProperty=Properties.at(Players.at(order)->get_position());
    switch(tempProperty->get_type()){

    case PROPERTY:

        if(tempProperty->owner==nullptr){

            ui->pushButton_5->show();

            ui->pushButton_5->setEnabled(true);

        }
        else{

            if(!tempProperty->get_mortgaged()&& tempProperty->owner!=Players.at(order)){//ejare

                 QMessageBox::information(this,"Information","This property is owned by "+QString::fromStdString(tempProperty->owner->get_nickname())+"\n"+" pay up!");


                 int tempRent;

                 switch (tempProperty->get_number_of_houses()) {

                 case 0:

                     if(Monopoly(tempProperty->get_color(),tempProperty->owner)){

                         tempRent=2*(tempProperty->get_rent0());

                     }
                     else{

                        tempRent=tempProperty->get_rent0();

                     }



                     break;

                 case 1:

                     tempRent=tempProperty->get_rent1();
                     break;
                 case 2:

                     tempRent=tempProperty->get_rent2();
                     break;
                 case 3:

                     tempRent=tempProperty->get_rent3();
                     break;
                 case 4:

                     tempRent=tempProperty->get_rent4();
                     break;
                 case 5://hotel

                     tempRent=tempProperty->get_rentHotel();
                     break;

                 }


                 Players.at(order)->set_Munny(Players.at(order)->get_Munny()-tempRent);

                 BankruptCheck();

                 tempProperty->owner->set_Munny(tempProperty->owner->get_Munny()+tempRent);

                 print_order();




            }
            else if(tempProperty->get_mortgaged()&& tempProperty->owner!=Players.at(order)){//ejare nemigirim

            }


        }

    break;

    case CHANCE:

    {

        CommunityOrChance=false;

    Community_Chance * CC=new Community_Chance(CommunityOrChance,this);

    int code=CC->exec();

        if(code==Rejected){


            switch (ChanceCards.back()->get_function()) {


            case BOARDWALK:

                move(39);


                break;

            case GO:

                move(40);

                break;

            case ILLINOIS:

                move(24);

                break;

            case ST_CHARLES_GO:

                if(Players.at(order)->get_position()>11){

                    Players.at(order)->set_Munny(Players.at(order)->get_Munny()+200);

                    print_order();
                }


                move(11);

                break;
            case RAILROAD:

               if(Players.at(order)->get_position()==7){

                   RenderMovement(15);

               }
               else if(Players.at(order)->get_position()==22){

                   RenderMovement(25);
               }

               else if(Players.at(order)->get_position()==36){

                   RenderMovement(45);


               }





               if(Properties.at(Players.at(order)->get_position())->owner==nullptr){

                   ui->pushButton_5->show();

                   ui->pushButton_5->setEnabled(true);


               }
               else{

                   if(!Properties.at(Players.at(order)->get_position())->get_mortgaged()&& Properties.at(Players.at(order)->get_position())->owner!=Players.at(order)){

                   QMessageBox::information(this,"Information","You have to pay double the rental.");


                   int tempRent;

                   int numOfRailRoads=0;

                   for(int i=0;i<int(Properties.size());i++){

                       if(Properties.at(i)->owner==Properties.at(Players.at(order)->get_position())->owner && Properties.at(i)->get_color()=="black"){

                           numOfRailRoads++;


                       }

                   }

                   switch (numOfRailRoads) {

                   case 1:

                       tempRent=Properties.at(Players.at(order)->get_position())->get_rent1();

                       break;

                   case 2:

                       tempRent=Properties.at(Players.at(order)->get_position())->get_rent2();

                       break;

                   case 3:

                       tempRent=Properties.at(Players.at(order)->get_position())->get_rent3();

                       break;

                   case 4:

                       tempRent=Properties.at(Players.at(order)->get_position())->get_rent4();

                       break;


                   }


                    tempRent=tempRent*2;


                   Players.at(order)->set_Munny(Players.at(order)->get_Munny()-tempRent);

                    BankruptCheck();

                   Properties.at(Players.at(order)->get_position())->owner->set_Munny(Properties.at(Players.at(order)->get_position())->owner->get_Munny()+tempRent);

                   print_order();





               }
                    else if(Properties.at(Players.at(order)->get_position())->get_mortgaged()&& Properties.at(Players.at(order)->get_position())->owner!=Players.at(order)){

                   }
               }




                break;

            case RAILROAD2:

                if(Players.at(order)->get_position()==7){

                    RenderMovement(15);

                }
                else if(Players.at(order)->get_position()==22){

                    RenderMovement(25);
                }

                else if(Players.at(order)->get_position()==36){

                    RenderMovement(45);


                }



                if(Properties.at(Players.at(order)->get_position())->owner==nullptr){

                    ui->pushButton_5->show();

                    ui->pushButton_5->setEnabled(true);


                }
                else{

                    if(!Properties.at(Players.at(order)->get_position())->get_mortgaged()&& Properties.at(Players.at(order)->get_position())->owner!=Players.at(order)){


                        QMessageBox::information(this,"Information","You have to pay double the rental.");


                        int tempRent;

                        int numOfRailRoads=0;

                        for(int i=0;i<int(Properties.size());i++){

                            if(Properties.at(i)->owner==Properties.at(Players.at(order)->get_position())->owner && Properties.at(i)->get_color()=="black"){

                                numOfRailRoads++;


                            }

                        }

                        switch (numOfRailRoads) {

                        case 1:

                            tempRent=Properties.at(Players.at(order)->get_position())->get_rent1();

                            break;

                        case 2:

                            tempRent=Properties.at(Players.at(order)->get_position())->get_rent2();

                            break;

                        case 3:

                            tempRent=Properties.at(Players.at(order)->get_position())->get_rent3();

                            break;

                        case 4:

                            tempRent=Properties.at(Players.at(order)->get_position())->get_rent4();

                            break;


                        }


                         tempRent=tempRent*2;


                        Players.at(order)->set_Munny(Players.at(order)->get_Munny()-tempRent);

                      BankruptCheck();

                        Properties.at(Players.at(order)->get_position())->owner->set_Munny(Properties.at(Players.at(order)->get_position())->owner->get_Munny()+tempRent);

                        print_order();



}
                     else if(Properties.at(Players.at(order)->get_position())->get_mortgaged()&& Properties.at(Players.at(order)->get_position())->owner!=Players.at(order)){

                    }
                }

                break;

            case UTILIY:

                if(Players.at(order)->get_position()==7){

                    RenderMovement(12);

                }
                else if(Players.at(order)->get_position()==22){

                    RenderMovement(28);
                }

                else if(Players.at(order)->get_position()==36){

                    RenderMovement(52);


                }



                if(Properties.at(Players.at(order)->get_position())->owner==nullptr){

                    ui->pushButton_5->show();

                    ui->pushButton_5->setEnabled(true);


                }
                else{
                    if(!Properties.at(Players.at(order)->get_position())->get_mortgaged()&& Properties.at(Players.at(order)->get_position())->owner!=Players.at(order)){

                    ui->pushButton_9->show();

                    ui->pushButton_9->setEnabled(true);

                    ui->pushButton->hide();

                    ui->pushButton_3->hide();

                    ui->pushButton->setEnabled(false);

                    ui->pushButton_3->setEnabled(false);

                    ChanceToUtility=true;
                    }
                     else if(Properties.at(Players.at(order)->get_position())->get_mortgaged()&& Properties.at(Players.at(order)->get_position())->owner!=Players.at(order)){}

                }




                break;

            case DIVIDEND:

                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+50);

                print_order();



                break;


            case THREE_SPACES:


                move(Players.at(order)->get_position()-3);


            break;


            case GETOUT:

            Players.at(order)->set_jail(true);

            print_order();


            break;

        case JAIL_NO_GO:

            Players.at(order)->number_of_turns_in_jail=0;

            RenderMovement(10);

           order++;

           if(order>number_of_players-1){
               order=0;
           }

           BankruptCheck();

           Doubles=0;

           Double=false;




           if(Players.at(order)->number_of_turns_in_jail>-1){

               jail();

               Players.at(order)->number_of_turns_in_jail++;

           }
           else{


           print_order();

          ui->pushButton_2->setEnabled(true);

          ui->pushButton_2->show();



           ui->pushButton_3->hide();

           ui->pushButton_3->setEnabled(true);

            ui->pushButton_3->setVisible(false);




           ui->pushButton->hide();

            ui->pushButton->setEnabled(true);

            ui->pushButton->setVisible(false);



           ui->pushButton_5->hide();

            ui->pushButton_5->setEnabled(true);


            ui->pushButton_5->setVisible(false);

            JailCheck=true;

           }

            break;

            case REPAIRS:
            {

                int TotalHouses=0;

                int TotalHotels=0;


               for(int i=0;i<int(Players.at(order)->MyProperties.size());i++){


                   if(Players.at(order)->MyProperties.at(i)->get_type()==PROPERTY){

                   if(Players.at(order)->MyProperties.at(i)->get_number_of_houses()==5){

                       TotalHotels++;


                   }
                   else{

                       TotalHouses++;

                   }

                   }




               }

               int repairs=TotalHouses*40+TotalHotels*115;

               Players.at(order)->set_Munny(Players.at(order)->get_Munny()-repairs);

               print_order();

               BankruptCheck();

                }


                break;


            case POORTAX:

                Players.at(order)->set_Munny(Players.at(order)->get_Munny()-15);

                print_order();

                BankruptCheck();

                break;

            case READING_GO:

                if(Players.at(order)->get_position()>5){

                    Players.at(order)->set_Munny(Players.at(order)->get_Munny()+200);

                    print_order();
                }


                move(5);



                break;

            case ONE_FIFTY:

                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+150);

                print_order();


                break;

            case FIFTY_FOR_EVERYONE:

            {

                for(int i=0;i<int(Players.size());i++){

                    if(Players.at(i)!=Players.at(order)){

                 Players.at(i)->set_Munny(Players.at(i)->get_Munny()+50);


                 Players.at(order)->set_Munny(Players.at(order)->get_Munny()-50);

                    }

                    }


                BankruptCheck();





                 print_order();

                break;




            }


        }


            if(ChanceCards.back()->get_function()!=GETOUT){



           Chance * temp=ChanceCards.back();

            ChanceCards.erase(ChanceCards.end()-1);

            ChanceCards.insert(ChanceCards.begin(),temp);
            }
            else{

                 ChanceCards.erase(ChanceCards.end()-1);

            }

        }


}

        break;

    case COMMUNITY:
    {

         CommunityOrChance=true;

     Community_Chance * CC2=new Community_Chance(CommunityOrChance,this);

        int code=CC2->exec();

        if(code==Rejected){

            switch (CommunityCards.back()->get_function()) {



            case GO_:

                move(40);



           break;

              case BANK200:

                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+200);

                print_order();



                break;

            case DOCTOR50:

                Players.at(order)->set_Munny(Players.at(order)->get_Munny()-50);

                print_order();

               BankruptCheck();
                break;

            case STOCK45:

                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+45);

                print_order();



                break;

            case FIFTY_FROM_EVERYONE:

            {
                for(int i=0;i<int(Players.size());i++){

                    if(Players.at(i)!=Players.at(order)){

                 Players.at(i)->set_Munny(Players.at(i)->get_Munny()-50);

                 Players.at(order)->set_Munny(Players.at(order)->get_Munny()+50);



                    }

                    }





                 print_order();

                 }

                break;


                case GETOUT_:

                Players.at(order)->set_jail(true);

                print_order();


                break;

            case JAIL_NO_GO_:

                Players.at(order)->number_of_turns_in_jail=0;

                RenderMovement(10);

               order++;

               if(order>number_of_players-1){
                   order=0;
               }

             BankruptCheck();

               Doubles=0;

               Double=false;




               if(Players.at(order)->number_of_turns_in_jail>-1){

                   jail();

                   Players.at(order)->number_of_turns_in_jail++;

               }
               else{


               print_order();

              ui->pushButton_2->setEnabled(true);

              ui->pushButton_2->show();



               ui->pushButton_3->hide();

               ui->pushButton_3->setEnabled(true);

                ui->pushButton_3->setVisible(false);




               ui->pushButton->hide();

                ui->pushButton->setEnabled(true);

                ui->pushButton->setVisible(false);



               ui->pushButton_5->hide();

                ui->pushButton_5->setEnabled(true);


                ui->pushButton_5->setVisible(false);

                JailCheck=true;

               }

                break;


            case TAX20:


                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+20);

                print_order();



                break;

            case INSURANCE100:
                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+100);

                print_order();




                break;

            case HOSPITAL100:
                Players.at(order)->set_Munny(Players.at(order)->get_Munny()-100);

                print_order();

                 BankruptCheck();

                break;

            case SCHOOL150:
                Players.at(order)->set_Munny(Players.at(order)->get_Munny()-150);

                print_order();

                BankruptCheck();


                break;

            case SERVICE25:
                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+25);

                print_order();



                break;

            case XMAS100:
                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+100);

                print_order();




                break;

            case REPAIRS_:
            {

                int TotalHouses=0;

                int TotalHotels=0;


               for(int i=0;i<int(Players.at(order)->MyProperties.size());i++){


                   if(Players.at(order)->MyProperties.at(i)->get_type()==PROPERTY){

                   if(Players.at(order)->MyProperties.at(i)->get_number_of_houses()==5){

                       TotalHotels++;


                   }
                   else{

                       TotalHouses++;

                   }

                   }




               }

               int repairs=TotalHouses*40+TotalHotels*115;

               Players.at(order)->set_Munny(Players.at(order)->get_Munny()-repairs);

               print_order();

               BankruptCheck();
                }
                break;

            case BEAUTY20:

                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+10);

                print_order();




                break;

            case INHERIT100:

                Players.at(order)->set_Munny(Players.at(order)->get_Munny()+100);

                print_order();











  }

             if(CommunityCards.back()->get_function()!=GETOUT_){


            Community * temp=CommunityCards.back();

            CommunityCards.erase(CommunityCards.end()-1);

            CommunityCards.insert(CommunityCards.begin(),temp);
             }
             else{

                  CommunityCards.erase(CommunityCards.end()-1);

             }


        }
    }

        break;

    case INCOMETAX:

        QMessageBox::information(this,"Information","You have landed on Income tax,10% of your income will go to the government.");

        Players.at(order)->set_Munny(int(0.9*Players.at(order)->get_Munny()));

        print_order();



        break;

    case LUXURYTAX:

        QMessageBox::information(this,"Information","You have landed on Luxury tax,you'll be charged 75$.");

        Players.at(order)->set_Munny(Players.at(order)->get_Munny()-75);

        print_order();

        BankruptCheck();
        break;

    case JAIL:


         break;

    case GO__:

     break;
    case PARKING:

      break;

    case GOTOJAIL:


        QMessageBox::information(this,"Information","You shall go to jail!");

        Players.at(order)->number_of_turns_in_jail=0;

        RenderMovement(10);

       order++;

       if(order>number_of_players-1){
           order=0;
       }

       BankruptCheck();

       Doubles=0;

       Double=false;




       if(Players.at(order)->number_of_turns_in_jail>-1){

           jail();

           Players.at(order)->number_of_turns_in_jail++;

       }
       else{


       print_order();

      ui->pushButton_2->setEnabled(true);

      ui->pushButton_2->show();



       ui->pushButton_3->hide();

       ui->pushButton_3->setEnabled(true);

        ui->pushButton_3->setVisible(false);




       ui->pushButton->hide();

        ui->pushButton->setEnabled(true);

        ui->pushButton->setVisible(false);



       ui->pushButton_5->hide();

        ui->pushButton_5->setEnabled(true);


        ui->pushButton_5->setVisible(false);

        JailCheck=true;

       }

        break;

    case RR:

        if(tempProperty->owner==nullptr){

            ui->pushButton_5->show();

            ui->pushButton_5->setEnabled(true);

        }
        else{

            if(!tempProperty->get_mortgaged() &&tempProperty->owner!=Players.at(order)){//ejare

                 QMessageBox::information(this,"Information","This property is owned by "+QString::fromStdString(tempProperty->owner->get_nickname())+"\n"+" pay up!");


                 int tempRent;

                 int numOfRailRoads=0;

                 for(int i=0;i<int(Properties.size());i++){

                     if(Properties.at(i)->owner==tempProperty->owner && Properties.at(i)->get_color()=="black"){

                         numOfRailRoads++;


                     }

                 }

                 switch (numOfRailRoads) {

                 case 1:

                     tempRent=tempProperty->get_rent1();

                     break;

                 case 2:

                     tempRent=tempProperty->get_rent2();

                     break;

                 case 3:

                     tempRent=tempProperty->get_rent3();

                     break;

                 case 4:

                     tempRent=tempProperty->get_rent4();

                     break;


                 }


                 Players.at(order)->set_Munny(Players.at(order)->get_Munny()-tempRent);

               BankruptCheck();

                 tempProperty->owner->set_Munny(tempProperty->owner->get_Munny()+tempRent);

                 print_order();




            }
            else if(tempProperty->get_mortgaged() &&tempProperty->owner!=Players.at(order)){//ejare nemigirim

            }

            }

        break;

    case UTILITY_:

        if(tempProperty->owner==nullptr){

            ui->pushButton_5->show();

            ui->pushButton_5->setEnabled(true);

        }
        else{

            if(!tempProperty->get_mortgaged()&&tempProperty->owner!=Players.at(order)){//ejare

                 QMessageBox::information(this,"Information","This property is owned by "+QString::fromStdString(tempProperty->owner->get_nickname())+"\n"+" pay up!");


                 int tempRent;

                 int numOfUtilities=0;

                 for(int i=0;i<int(Properties.size());i++){

                     if(Properties.at(i)->owner==tempProperty->owner && Properties.at(i)->get_color()=="white"){

                        numOfUtilities++;


                     }

                 }

                 if(numOfUtilities==1){
                     tempRent=tempProperty->get_multiplier1() *(Dice1+Dice2);
                 }
                 else{
                     tempRent=tempProperty->get_multiplier2() *(Dice1+Dice2);
                 }


                 Players.at(order)->set_Munny(Players.at(order)->get_Munny()-tempRent);

                BankruptCheck();
                 tempProperty->owner->set_Munny(tempProperty->owner->get_Munny()+tempRent);

                 print_order();




            }
            else if(tempProperty->get_mortgaged()&&tempProperty->owner!=Players.at(order)){//ejare nemigirim

            }

            }


        break;



}
}

void GameBoard::rollDice(){


    JailCheck=false;

      Double=throwDice(Dice1,Dice2);

      if(Double==true){
          Doubles++;


          if(Doubles==3){

              Double=false;

              Doubles=0;

              RenderMovement(10);

              Players.at(order)->number_of_turns_in_jail=0;

              order++;

              if(order>number_of_players-1){

                  order=0;

              }
              BankruptCheck();

              QMessageBox::warning(this,"Warning","You rolled 3 doubles,you'll go to jail!");




             JailCheck=true;

        }

        else{
          QMessageBox::information(this,"Information","You rolled a double,you get to roll again!");
          }
      }
      else{
          Doubles=0;
      }


      if(!JailCheck){


      printDice(Dice1,Dice2);


      RenderMovement(Players.at(order)->get_position()+Dice1+Dice2);



      SituationCheck();

      if(JailCheck){



          print_order();

          ui->pushButton_2->setEnabled(true);

          ui->pushButton_2->show();


          ui->pushButton_3->hide();

          ui->pushButton_3->setEnabled(false);

          ui->pushButton->hide();

          ui->pushButton->setEnabled(false);

          ui->pushButton_5->hide();

          ui->pushButton_5->setEnabled(false);





      }
      else{

      ui->pushButton_3->show();

      ui->pushButton_3->setEnabled(true);

      ui->pushButton->show();

      ui->pushButton->setEnabled(true);

      ui->pushButton_2->setEnabled(false);

      ui->pushButton_2->hide();
      }

  }
      else{

          print_order();

          ui->pushButton_2->setEnabled(true);

          ui->pushButton_2->show();


          ui->pushButton_3->hide();

          ui->pushButton_3->setEnabled(false);

          ui->pushButton->hide();

          ui->pushButton->setEnabled(false);

          ui->pushButton_5->hide();

          ui->pushButton_5->setEnabled(false);




      }

      if(Players.at(order)->number_of_turns_in_jail>-1){

          jail();

          Players.at(order)->number_of_turns_in_jail++;

      }

      if(ChanceToUtility){

          ChanceToUtility=false;

          ui->pushButton_3->hide();

          ui->pushButton_3->setEnabled(false);

          ui->pushButton->hide();

          ui->pushButton->setEnabled(false);


      }

  }

void GameBoard::on_pushButton_2_clicked()//roll dice
{

  rollDice();


}

  void GameBoard::on_pushButton_3_clicked()//end turn
  {


      if(Doubles>0){

      }
      else{

          order++;


      }
      if(order>number_of_players-1){

          order=0;

      }

     BankruptCheck();




      if(Players.at(order)->number_of_turns_in_jail>-1){

          jail();

          Players.at(order)->number_of_turns_in_jail++;

      }
      else{



      print_order();

      ui->pushButton_2->setEnabled(true);

      ui->pushButton_2->show();


      ui->pushButton_3->hide();

      ui->pushButton_3->setEnabled(false);

      ui->pushButton->hide();

      ui->pushButton->setEnabled(false);

      ui->pushButton_5->hide();

      ui->pushButton_5->setEnabled(false);

      }
}



  void GameBoard::HideBuyButton(){

      ui->pushButton_5->hide();

      ui->pushButton_5->setEnabled(false);

  }

void GameBoard::on_pushButton_5_clicked()//buy property
{

    if(Properties.at(Players.at(order)->get_position())->owner==nullptr){

        Buy * buy=new Buy(this);

        int code=buy->exec();

        if(code==Accepted || code==Rejected){
             BankruptCheck();
        }


    }


}

void GameBoard::on_pushButton_6_clicked()//roll to get out of jail
{
    Double=throwDice(Dice1,Dice2);

    printDice(Dice1,Dice2);

    if(Double){

        RenderMovement(Players.at(order)->get_position()+Dice1+Dice2);

        SituationCheck();

        ui->pushButton_3->show();

        ui->pushButton_3->setEnabled(true);

        ui->pushButton->show();

        ui->pushButton->setEnabled(true);

        ui->pushButton_2->setEnabled(false);

        ui->pushButton_2->hide();

        ui->pushButton_6->setEnabled(false);

        ui->pushButton_6->hide();

        ui->pushButton_7->setEnabled(false);

        ui->pushButton_7->hide();

        ui->pushButton_8->setEnabled(false);

        ui->pushButton_8->hide();


         QMessageBox::information(this,"Information","You rolled a double,you can get out of jail!");

         Double=false;

    Players.at(order)->number_of_turns_in_jail=-1;

    }
    else{

        if(Players.at(order)->number_of_turns_in_jail==3){

            Players.at(order)->set_Munny(Players.at(order)->get_Munny()-50);



           BankruptCheck();

             print_order();

            RenderMovement(Players.at(order)->get_position()+Dice1+Dice2);

            SituationCheck();

            ui->pushButton_3->show();

            ui->pushButton_3->setEnabled(true);

            ui->pushButton->show();

            ui->pushButton->setEnabled(true);

            ui->pushButton_2->setEnabled(false);

            ui->pushButton_2->hide();

            ui->pushButton_6->setEnabled(false);

            ui->pushButton_6->hide();

            ui->pushButton_7->setEnabled(false);

            ui->pushButton_7->hide();

            ui->pushButton_8->setEnabled(false);

            ui->pushButton_8->hide();

             QMessageBox::information(this,"Information","You payed 50$,you can get out of jail!");

              Players.at(order)->number_of_turns_in_jail=-1;



        }

        else{



        ui->pushButton_3->show();

        ui->pushButton_3->setEnabled(true);

        ui->pushButton->show();

        ui->pushButton->setEnabled(true);

        ui->pushButton_2->setEnabled(false);

        ui->pushButton_2->hide();

        ui->pushButton_6->setEnabled(false);

        ui->pushButton_6->hide();

        ui->pushButton_7->setEnabled(false);

        ui->pushButton_7->hide();

        ui->pushButton_8->setEnabled(false);

        ui->pushButton_8->hide();

        }

    }




}

void GameBoard::on_pushButton_7_clicked()//50 to get out
{
    Players.at(order)->set_Munny(Players.at(order)->get_Munny()-50);

     BankruptCheck();

    print_order();



    ui->pushButton_2->setEnabled(true);

    ui->pushButton_2->show();

    ui->pushButton_6->setEnabled(false);

    ui->pushButton_6->hide();

    ui->pushButton_7->setEnabled(false);

    ui->pushButton_7->hide();

    ui->pushButton_8->setEnabled(false);

    ui->pushButton_8->hide();

    QMessageBox::information(this,"Information","You're free!");

     Players.at(order)->number_of_turns_in_jail=-1;




}

void GameBoard::on_pushButton_8_clicked()
{

    Players.at(order)->set_jail(false);

    print_order();

    ui->pushButton_2->setEnabled(true);

    ui->pushButton_2->show();

    ui->pushButton_6->setEnabled(false);

    ui->pushButton_6->hide();

    ui->pushButton_7->setEnabled(false);

    ui->pushButton_7->hide();

    ui->pushButton_8->setEnabled(false);

    ui->pushButton_8->hide();

    QMessageBox::information(this,"Information","You're free!");

    Players.at(order)->number_of_turns_in_jail=-1;


}

void GameBoard::on_pushButton_clicked()
{
    my_Properties *My_properties=new my_Properties(this);

    int code=My_properties->exec();

    if(code==Accepted || code==Rejected){
        BankruptCheck();
    }

}

void GameBoard::on_pushButton_9_clicked()
{

    ui->pushButton_9->hide();

    ui->pushButton_9->setEnabled(false);

    throwDice(Dice1,Dice2);

    printDice(Dice1,Dice2);

    QMessageBox::information(this,"Information","You have to pay 10x the amount of dice.");

    Players.at(order)->set_Munny(Players.at(order)->get_Munny()-10*(Dice1+Dice2));

    BankruptCheck();

    print_order();




    ui->pushButton->show();

    ui->pushButton_3->show();

    ui->pushButton->setEnabled(true);

    ui->pushButton_3->setEnabled(true);

}

void GameBoard::on_pushButton_10_clicked()
{
    ui->pushButton_10->hide();

    ui->pushButton_10->setEnabled(false);


    ui->label_58->show();

    ui->label_58->setEnabled(true);

    ui->label_59->show();

    ui->label_59->setEnabled(true);

    ui->pushButton_11->show();

    ui->pushButton_11->setEnabled(true);

    ui->comboBox->show();

    ui->comboBox->setEnabled(true);

    ui->lineEdit->show();

    ui->lineEdit->setEnabled(true);

    ui->comboBox->clear();

    for(int i=0;i<int(Players.size());i++){

        if(Players.at(i)!=Players.at(order)){

        ui->comboBox->addItem(QString::fromStdString(Players.at(i)->get_nickname()));


}
    }

    ui->comboBox->setCurrentIndex(-1);

    ui->lineEdit->clear();



}

void GameBoard::on_pushButton_11_clicked()
{

    if(ui->comboBox->currentIndex()!=-1){

        if(!Empty_string_check(ui->lineEdit->text().toUtf8().constData()) && IsNumber(ui->lineEdit->text().toUtf8().constData()) &&ui->lineEdit->text().toInt()>0 ){

            QMessageBox::StandardButton reply;

             reply = QMessageBox::question(this, "Offer",ui->comboBox->currentText()+ " do you want to buy this get out of jail card for "+ui->lineEdit->text() + " ?",

                                           QMessageBox::Yes|QMessageBox::No);


             if (reply == QMessageBox::Yes) {

                 int buyer=0;

                 for(int i=0;i<int(Players.size());i++){


                     if(QString::fromStdString(Players.at(i)->get_nickname())==ui->comboBox->currentText()){

                         buyer=i;
                     }

                 }






                 Players.at(order)->set_jail(false);


                Players.at(buyer)->set_jail(true);


                 Players.at(buyer)->set_Munny(Players.at(buyer)->get_Munny()-ui->lineEdit->text().toInt());

                 Players.at(order)->set_Munny(Players.at(order)->get_Munny()+ui->lineEdit->text().toInt());

                 print_order();


                QMessageBox::information(this,"Information",ui->comboBox->currentText()+" bought this get out of jail card from you.");


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
