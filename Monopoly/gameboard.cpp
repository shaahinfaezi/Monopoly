#include "gameboard.h"
#include "ui_gameboard.h"
#include <QDebug>
#include "QPixmap"
#include <QScreen>
#include <QDebug>
#include <QPainter>

#include <stdlib.h>
#include <time.h>

#include "vector"




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

void throwDice(int &Dice1,int &Dice2){



    Dice1=rand() % 6 + 1;

    Dice2=rand() % 6 + 1;



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


/////////////
    QPixmap pix=*new QPixmap(":/res/Images/pic5.png.crdownload");

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

                ui->label_2->setGeometry(ui->label_2->x(),ui->label_2->y(),78,209);

                ui->label_2->setPixmap(pic.scaled(ui->label_2->width(),ui->label_2->height(),Qt::KeepAspectRatio));

                qDebug()<<ui->label_2->width();



                QPixmap pic1(":/res/Images/photos/photo20.jpg");

                ui->label_3->setGeometry(ui->label_3->x(),ui->label_3->y(),78,209);

                ui->label_3->setPixmap(pic1.scaled(ui->label_3->width(),ui->label_3->height(),Qt::KeepAspectRatio));


                QPixmap pic2(":/res/Images/photos/photo19.jpg");

                ui->label_4->setGeometry(ui->label_4->x(),ui->label_4->y(),78,220);

                ui->label_4->setPixmap(pic2.scaled(ui->label_4->width(),ui->label_4->height(),Qt::KeepAspectRatio));


                QPixmap pic3(":/res/Images/photos/photo18.jpg");

                ui->label_5->setGeometry(ui->label_5->x(),ui->label_5->y(),78,220);

                ui->label_5->setPixmap(pic3.scaled(ui->label_5->width(),ui->label_5->height(),Qt::KeepAspectRatio));


                QPixmap pic4(":/res/Images/photos/photo1.jpg");

                ui->label_6->setGeometry(ui->label_6->x(),ui->label_6->y(),78,209);

                ui->label_6->setPixmap(pic4.scaled(ui->label_6->width(),ui->label_6->height(),Qt::KeepAspectRatio));


                QPixmap pic5(":/res/Images/photos/photo3.jpg");

                ui->label_7->setGeometry(ui->label_7->x(),ui->label_7->y(),78,209);

                ui->label_7->setPixmap(pic5.scaled(ui->label_7->width(),ui->label_7->height(),Qt::KeepAspectRatio));

                QPixmap pic6(":/res/Images/photos/photo13.jpg");

                ui->label_8->setGeometry(ui->label_8->x(),ui->label_8->y(),78,209);

                ui->label_8->setPixmap(pic6.scaled(ui->label_8->width(),ui->label_8->height(),Qt::KeepAspectRatio));



                QPixmap pic7(":/res/Images/photos/community chest2.png");

                ui->label_9->setGeometry(ui->label_9->x(),ui->label_9->y(),78,209);

                ui->label_9->setPixmap(pic7.scaled(ui->label_9->width(),ui->label_9->height(),Qt::KeepAspectRatio));



                QPixmap pic8(":/res/Images/photos/photo14.jpg");

                ui->label_10->setGeometry(ui->label_10->x(),ui->label_10->y(),78,209);

                ui->label_10->setPixmap(pic8.scaled(ui->label_10->width(),ui->label_10->height(),Qt::KeepAspectRatio));


              ///////////////////////////////////////////
                QPixmap pic9(":/res/Images/bord/photo_2022-06-27_21-51-45.jpg");

                ui->label_20->setGeometry(ui->label_20->x(),ui->label_20->y(),141,131);
                ui->label_20->setPixmap(pic9.scaled(ui->label_20->width(),ui->label_20->height(),Qt::KeepAspectRatio));

////////////////////////////////

                QPixmap pix3=*new QPixmap(":/res/Images/photos/photo28.jpg");

                    QMatrix m3;

                    m3.rotate(90);

                    pix3=pix3.transformed(m3);
                    ui->label_11->setGeometry(ui->label_11->x(),ui->label_11->y(),129,78);

                    ui->label_11->setPixmap(pix3.scaled(ui->label_11->width(),ui->label_11->height(),Qt::KeepAspectRatio));



                QPixmap pix4=*new QPixmap(":/res/Images/photos/photo27.jpg");

                     QMatrix m4;

                     m4.rotate(90);

                      pix4=pix4.transformed(m4);
                       ui->label_12->setGeometry(ui->label_12->x(),ui->label_12->y(),129,78) ;

                      ui->label_12->setPixmap(pix4.scaled(ui->label_12->width(),ui->label_12->height(),Qt::KeepAspectRatio));



                  QPixmap pix5=*new QPixmap(":/res/Images/photos/community chest2.png");

                      QMatrix m5;

                       m5.rotate(90);

                       pix5=pix5.transformed(m5);
                       ui->label_13->setGeometry(ui->label_13->x(),ui->label_13->y(),129,78);

                      ui->label_13->setPixmap(pix5.scaled(ui->label_13->width(),ui->label_13->height(),Qt::KeepAspectRatio));



                   QPixmap pix6=*new QPixmap(":/res/Images/photos/photo26.jpg");

                   QMatrix m6;

                    m6.rotate(90);

                    pix6=pix6.transformed(m6);
                    ui->label_14->setGeometry(ui->label_14->x(),ui->label_14->y(),129,78);

                     ui->label_14->setPixmap(pix6.scaled(ui->label_14->width(),ui->label_14->height(),Qt::KeepAspectRatio));




                    QPixmap pix7=*new QPixmap(":/res/Images/photos/photo5.jpg");

                    QMatrix m7;

                    m7.rotate(90);

                    pix7=pix7.transformed(m7);
                     ui->label_15->setGeometry(ui->label_15->x(),ui->label_15->y(),129,78);
                    ui->label_15->setPixmap(pix7.scaled(ui->label_15->width(),ui->label_15->height(),Qt::KeepAspectRatio));



                    QPixmap pix8=*new QPixmap(":/res/Images/photos/photo25.jpg");

                    QMatrix m8;

                    m8.rotate(90);

                    pix8=pix8.transformed(m8);
                    ui->label_16->setGeometry(ui->label_16->x(),ui->label_16->y(),129,78);
                    ui->label_16->setPixmap(pix8.scaled(ui->label_16->width(),ui->label_16->height(),Qt::KeepAspectRatio));


                    QPixmap pix9=*new QPixmap(":/res/Images/photos/photo24.jpg");

                    QMatrix m9;

                    m9.rotate(90);

                    pix9=pix9.transformed(m9);
                    ui->label_17->setGeometry(ui->label_17->x(),ui->label_17->y(),129,78);
                    ui->label_17->setPixmap(pix9.scaled(ui->label_17->width(),ui->label_17->height(),Qt::KeepAspectRatio));


                    QPixmap pix10=*new QPixmap(":/res/Images/photos/photo23.jpg");

                    QMatrix m10;

                    m10.rotate(90);

                    pix10=pix10.transformed(m10);
                      ui->label_18->setGeometry(ui->label_18->x(),ui->label_18->y(),129,78);
                    ui->label_18->setPixmap(pix10.scaled(ui->label_18->width(),ui->label_18->height(),Qt::KeepAspectRatio));


                    QPixmap pix11=*new QPixmap(":/res/Images/photos/photo22.jpg");

                    QMatrix m11;

                    m11.rotate(90);

                    pix11=pix11.transformed(m11);
                    ui->label_19->setGeometry(ui->label_19->x(),ui->label_19->y(),129,78);
                    ui->label_19->setPixmap(pix11.scaled(ui->label_19->width(),ui->label_19->height(),Qt::KeepAspectRatio));


///////////////////////////////////////
                     QPixmap pic10(":/res/Images/bord/photo_2022-06-27_21-51-42.jpg");
                    ui->label_21->setGeometry(ui->label_21->x(),ui->label_21->y(),141,131);
                    ui->label_21->setPixmap(pic10.scaled(ui->label_21->width(),ui->label_21->height(),Qt::KeepAspectRatio));



//////////////

                     QPixmap pix12=*new QPixmap(":/res/Images/photos/photo36.jpg");

                     QMatrix m12;

                     m12.rotate(180);

                     pix12=pix12.transformed(m12);
                     ui->label_23->setGeometry(ui->label_23->x(),ui->label_23->y(),78,129);
                     ui->label_23->setPixmap(pix12.scaled(ui->label_23->width(),ui->label_23->height(),Qt::KeepAspectRatio));



                     QPixmap pix13=*new QPixmap(":/res/Images/photos/photo39.jpg");

                     QMatrix m13;

                     m13.rotate(180);

                     pix13=pix13.transformed(m13);
                     ui->label_29->setGeometry(ui->label_29->x(),ui->label_29->y(),78,129);
                     ui->label_29->setPixmap(pix13.scaled(ui->label_29->width(),ui->label_29->height(),Qt::KeepAspectRatio));




                     QPixmap pix14=*new QPixmap(":/res/Images/photos/photo37.jpg");

                     QMatrix m14;

                     m14.rotate(180);

                     pix14=pix14.transformed(m14);
                     ui->label_30->setGeometry(ui->label_30->x(),ui->label_30->y(),78,129);
                     ui->label_30->setPixmap(pix14.scaled(ui->label_30->width(),ui->label_30->height(),Qt::KeepAspectRatio));




                     QPixmap pix15=*new QPixmap(":/res/Images/photos/photo38.jpg");

                     QMatrix m15;

                     m15.rotate(180);

                     pix15=pix15.transformed(m15);
                     ui->label_26->setGeometry(ui->label_26->x(),ui->label_26->y(),78,129);
                     ui->label_26->setPixmap(pix15.scaled(ui->label_26->width(),ui->label_26->height(),Qt::KeepAspectRatio));




                     QPixmap pix16=*new QPixmap(":/res/Images/photos/photo8.jpg");

                     QMatrix m16;

                     m16.rotate(180);

                     pix16=pix16.transformed(m16);
                     ui->label_27->setGeometry(ui->label_27->x(),ui->label_27->y(),78,129);
                     ui->label_27->setPixmap(pix16.scaled(ui->label_27->width(),ui->label_27->height(),Qt::KeepAspectRatio));




                     QPixmap pix17=*new QPixmap(":/res/Images/photos/photo29.jpg");

                     QMatrix m17;

                     m17.rotate(180);

                     pix17=pix17.transformed(m17);
                     ui->label_22->setGeometry(ui->label_22->x(),ui->label_22->y(),78,129);
                     ui->label_22->setPixmap(pix17.scaled(ui->label_22->width(),ui->label_22->height(),Qt::KeepAspectRatio));




                     QPixmap pix18=*new QPixmap(":/res/Images/photos/photo30.jpg");

                     QMatrix m18;

                     m18.rotate(180);

                     pix18=pix18.transformed(m18);
                     ui->label_24->setGeometry(ui->label_24->x(),ui->label_24->y(),78,129);
                     ui->label_24->setPixmap(pix18.scaled(ui->label_24->width(),ui->label_24->height(),Qt::KeepAspectRatio));





                     QPixmap pix19=*new QPixmap(":/res/Images/photos/photo31.jpg");

                     QMatrix m19;

                     m19.rotate(180);

                     pix19=pix19.transformed(m19);
                     ui->label_25->setGeometry(ui->label_25->x(),ui->label_25->y(),78,129);
                     ui->label_25->setPixmap(pix19.scaled(ui->label_25->width(),ui->label_25->height(),Qt::KeepAspectRatio));




                     QPixmap pix20=*new QPixmap(":/res/Images/photos/photo32.jpg");

                     QMatrix m20;

                     m20.rotate(180);

                     pix20=pix20.transformed(m20);
                     ui->label_28->setGeometry(ui->label_28->x(),ui->label_28->y(),78,129);
                     ui->label_28->setPixmap(pix20.scaled(ui->label_28->width(),ui->label_28->height(),Qt::KeepAspectRatio));

     //////////////////////////

                     QPixmap pix21=*new QPixmap(":/res/Images/photos/photo17.jpg");

                     QMatrix m21;

                     m21.rotate(270);

                     pix21=pix21.transformed(m21);
                     ui->label_38->setGeometry(ui->label_38->x(),ui->label_38->y(),129,78);
                     ui->label_38->setPixmap(pix21.scaled(ui->label_38->width(),ui->label_38->height(),Qt::KeepAspectRatio));


                     QPixmap pix22=*new QPixmap(":/res/Images/photos/photo16.jpg");

                     QMatrix m22;

                     m22.rotate(270);

                     pix22=pix22.transformed(m22);
                     ui->label_36->setGeometry(ui->label_36->x(),ui->label_36->y(),129,78);
                     ui->label_36->setPixmap(pix22.scaled(ui->label_36->width(),ui->label_36->height(),Qt::KeepAspectRatio));



                     QPixmap pix23=*new QPixmap(":/res/Images/photos/community chest2.png");

                     QMatrix m23;

                     m23.rotate(270);

                     pix23=pix23.transformed(m23);
                     ui->label_33->setGeometry(ui->label_33->x(),ui->label_33->y(),129,78);
                     ui->label_33->setPixmap(pix23.scaled(ui->label_33->width(),ui->label_33->height(),Qt::KeepAspectRatio));



                     QPixmap pix24=*new QPixmap(":/res/Images/photos/photo15.jpg");

                     QMatrix m24;

                     m24.rotate(270);

                     pix24=pix24.transformed(m24);
                     ui->label_35->setGeometry(ui->label_35->x(),ui->label_35->y(),129,78);
                     ui->label_35->setPixmap(pix24.scaled(ui->label_35->width(),ui->label_35->height(),Qt::KeepAspectRatio));



                     QPixmap pix25=*new QPixmap(":/res/Images/photos/photo11.jpg");

                     QMatrix m25;

                     m25.rotate(270);

                     pix25=pix25.transformed(m25);
                     ui->label_34->setGeometry(ui->label_34->x(),ui->label_34->y(),129,78);
                     ui->label_34->setPixmap(pix25.scaled(ui->label_34->width(),ui->label_34->height(),Qt::KeepAspectRatio));



                     QPixmap pix26=*new QPixmap(":/res/Images/photos/photo10.jpg");

                     QMatrix m26;

                     m26.rotate(270);

                     pix26=pix26.transformed(m26);
                     ui->label_31->setGeometry(ui->label_31->x(),ui->label_31->y(),129,78);
                     ui->label_31->setPixmap(pix26.scaled(ui->label_31->width(),ui->label_31->height(),Qt::KeepAspectRatio));



                     QPixmap pix27=*new QPixmap(":/res/Images/photos/photo33.jpg");

                     QMatrix m27;

                     m27.rotate(270);

                     pix27=pix27.transformed(m27);
                     ui->label_37->setGeometry(ui->label_37->x(),ui->label_37->y(),129,78);
                     ui->label_37->setPixmap(pix27.scaled(ui->label_37->width(),ui->label_37->height(),Qt::KeepAspectRatio));




                     QPixmap pix28=*new QPixmap(":/res/Images/photos/photo34.jpg");

                     QMatrix m28;

                     m28.rotate(270);

                     pix28=pix28.transformed(m28);
                     ui->label_32->setGeometry(ui->label_32->x(),ui->label_32->y(),129,78);
                     ui->label_32->setPixmap(pix28.scaled(ui->label_32->width(),ui->label_32->height(),Qt::KeepAspectRatio));



                     QPixmap pix29=*new QPixmap(":/res/Images/photos/photo35.jpg");

                     QMatrix m29;

                     m29.rotate(270);

                     pix29=pix29.transformed(m29);
                     ui->label_39->setGeometry(ui->label_39->x(),ui->label_39->y(),129,78);
                     ui->label_39->setPixmap(pix29.scaled(ui->label_39->width(),ui->label_39->height(),Qt::KeepAspectRatio));


//////////////////////
                     QPixmap pic11(":/res/Images/bord/go.png");
                     ui->label_40->setGeometry(ui->label_40->x(),ui->label_40->y(),141,131);
                     ui->label_40->setPixmap(pic11.scaled(ui->label_40->width(),ui->label_40->height(),Qt::KeepAspectRatio));

/////////////////////////
                     QPixmap pix30=*new QPixmap(":/res/Images/bord/photo_2022-06-27_21-51-35.jpg");

                     QMatrix m30;

                     m30.rotate(270);

                     pix30=pix30.transformed(m30);

                      ui->label_41->setGeometry(ui->label_41->x(),ui->label_41->y(),141,131);
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

    tempCommunity->set_function(GETOUT_);

    CommunityCards.push_back(tempCommunity);

    //

    tempCommunity=new Community();

    tempCommunity->set_path(":/res/Images/community/Community_Chest_GOOJF16.png");

    tempCommunity->set_function(FIFTY_FROM_EVERYONE);

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





        tokens_path.push_back(":/res/Images/mohre/18-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/17-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/16-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/15-removebg-preview.png");

        tokens_path.push_back(":/res/Images/mohre/trance14.png");

        tokens_path.push_back(":/res/Images/mohre/trance13.png");

        tokens_path.push_back(":/res/Images/mohre/trance12.png");

        tokens_path.push_back(":/res/Images/mohre/trance11.png");




    Randomizer(tokens_path);




    for(int i=0;i<number_of_players;i++){

        //sakhtane Player * va dadan be vector



        //Player tempPlayer=new Player(nicknames.at(i),);
        //Players.push_back(tempPlayer);


    }


    Randomizer(Players);

    int sums[number_of_players];

    srand(time(NULL));

    for(int i=0;i<number_of_players;i++){

        int Dice1,Dice2;

        throwDice(Dice1,Dice2);

        //neshoon dadan adade tas

        //sleep

        sums[i]=Dice1+Dice2;



    }

    for(int i=0;i<number_of_players;i++){

        for(int j=0;j<number_of_players-i-1;j++){

            if(sums[j+1]>sums[j]){


                int temp=sums[j+1];

                sums[j+1]=sums[j];

                sums[j]=temp;

                /*Player * tempPlayer=Players.at(j+1);

                Players.at(j+1)=Players.at(j);

                Players.at(j)=tempPlayer;
                */

            }
        }


    }






}

void GameBoard::print(){



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
