#include "my_properties.h"
#include "ui_my_properties.h"
#include <Property.h>
#include <QMessageBox>
#include <sell_property.h>

void my_Properties::listPrint(){


    ui->label_2->hide();

    ui->label_2->setEnabled(false);

    ui->label_3->hide();

    ui->label_3->setEnabled(false);

    ui->label_4->hide();

    ui->label_4->setEnabled(false);

    ui->label_5->hide();

    ui->label_5->setEnabled(false);

    ui->label_6->hide();

    ui->label_6->setEnabled(false);

    if(gameBoard->Players.at(gameBoard->order)->MyProperties.size()==0){

        ui->label->setText("You do not own a property at the moment.");


    ui->pushButton->hide();

    ui->pushButton->setEnabled(false);

    ui->pushButton_2->hide();

    ui->pushButton_2->setEnabled(false);

    ui->pushButton_3->hide();

    ui->pushButton_3->setEnabled(false);

    ui->pushButton_4->hide();

    ui->pushButton_4->setEnabled(false);

    ui->pushButton_5->hide();

    ui->pushButton_5->setEnabled(false);

    ui->pushButton_7->hide();

    ui->pushButton_7->setEnabled(false);

    ui->pushButton_6->hide();

    ui->pushButton_6->setEnabled(false);

    ui->pushButton_8->hide();

    ui->pushButton_8->setEnabled(false);

    ui->label_2->hide();

    ui->label_2->setEnabled(false);

    ui->label_3->hide();

    ui->label_3->setEnabled(false);

    ui->label_4->hide();

    ui->label_4->setEnabled(false);

    ui->label_5->hide();

    ui->label_5->setEnabled(false);

    ui->label_6->hide();

    ui->label_6->setEnabled(false);


    }
    else{
        ui->pushButton_6->show();

        ui->pushButton_6->setEnabled(true);

        ui->pushButton_8->show();

        ui->pushButton_8->setEnabled(true);

       if(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_type()==PROPERTY) {

           QPixmap housepix(":/res/Images/photo_2022-07-01_11-11-57__2_-removebg-preview.png");

           QPixmap hotelpix(":/res/Images/photo_2022-07-01_11-11-57-removebg-preview.png");


           switch (gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_number_of_houses()) {

           case 0:

            break;

           case 1:
               ui->label_2->show();

               ui->label_2->setEnabled(true);

               ui->label_2->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

            break;

           case 2:

               ui->label_2->show();

               ui->label_2->setEnabled(true);

               ui->label_3->show();

               ui->label_3->setEnabled(true);

               ui->label_2->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

               ui->label_3->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

            break;

           case 3:

               ui->label_2->show();

               ui->label_2->setEnabled(true);

               ui->label_3->show();

               ui->label_3->setEnabled(true);

               ui->label_4->show();

               ui->label_4->setEnabled(true);

               ui->label_2->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

               ui->label_3->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

               ui->label_4->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

            break;

           case 4:
               ui->label_2->show();

               ui->label_2->setEnabled(true);

               ui->label_3->show();

               ui->label_3->setEnabled(true);

               ui->label_4->show();

               ui->label_4->setEnabled(true);

               ui->label_5->show();

               ui->label_5->setEnabled(true);



               ui->label_2->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

               ui->label_3->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

               ui->label_4->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

               ui->label_5->setPixmap(housepix.scaled(51,51,Qt::KeepAspectRatio));

            break;

           case 5:

               ui->label_6->show();

               ui->label_6->setEnabled(true);

               ui->label_6->setPixmap(hotelpix.scaled(51,51,Qt::KeepAspectRatio));

            break;







           }
       }


     if(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_type()==RR ||gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_type()==UTILITY_ ||gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_mortgaged()==true){

         ui->pushButton->hide();

         ui->pushButton->setEnabled(false);

         ui->pushButton_2->hide();

         ui->pushButton_2->setEnabled(false);


         ui->pushButton_4->hide();

         ui->pushButton_4->setEnabled(false);

         ui->pushButton_5->hide();

         ui->pushButton_5->setEnabled(false);


     }
     else{
         if(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_number_of_houses()==5){


             ui->pushButton->hide();

             ui->pushButton->setEnabled(false);

             ui->pushButton_2->hide();

             ui->pushButton_2->setEnabled(false);

             ui->pushButton_4->hide();

             ui->pushButton_4->setEnabled(false);


         }
         else{


             ui->pushButton->show();

             ui->pushButton->setEnabled(true);

             ui->pushButton_2->show();

             ui->pushButton_2->setEnabled(true);

             ui->pushButton_4->show();

             ui->pushButton_4->setEnabled(true);

             ui->pushButton_5->show();

             ui->pushButton_5->setEnabled(true);




         }



     }

  QPixmap pixmap(QString::fromStdString(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_PropertyCard()));

  ui->label->setPixmap(pixmap.scaled(422,574,Qt::KeepAspectRatio));



}




}

my_Properties::my_Properties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::my_Properties)
{
    ui->setupUi(this);

    gameBoard=GameBoard::get_instance();

    setWindowTitle("My Properties");

    iterator=0;

    if(gameBoard->Players.at(gameBoard->order)->MyProperties.size()==0){

        ui->label->setText("You do not own a property at the moment.");


    ui->pushButton->hide();

    ui->pushButton->setEnabled(false);

    ui->pushButton_2->hide();

    ui->pushButton_2->setEnabled(false);

    ui->pushButton_3->hide();

    ui->pushButton_3->setEnabled(false);

    ui->pushButton_4->hide();

    ui->pushButton_4->setEnabled(false);

    ui->pushButton_5->hide();

    ui->pushButton_5->setEnabled(false);

    ui->pushButton_7->hide();

    ui->pushButton_7->setEnabled(false);

    ui->pushButton_6->hide();

    ui->pushButton_6->setEnabled(false);

    ui->pushButton_8->hide();

    ui->pushButton_8->setEnabled(false);


    }
    else{



        ui->pushButton_6->setIcon(QIcon(":/res/Images/3017934_antecedent_arrow_earlier_left_outline_icon.png"));


         ui->pushButton_6->setIconSize(QSize(101, 101));

        ui->pushButton_8->setIcon(QIcon(":/res/Images/3017927_after_alongside_arrow_latter_next_icon.png"));


         ui->pushButton_8->setIconSize(QSize(101, 101));

        listPrint();
    }

}

my_Properties::~my_Properties()
{
    delete ui;
}

void my_Properties::on_pushButton_8_clicked()
{
    iterator++;

    if(iterator==int(gameBoard->Players.at(gameBoard->order)->MyProperties.size())){
        iterator=0;
    }

    listPrint();
}

void my_Properties::on_pushButton_6_clicked()
{
    iterator--;

    if(iterator==-1){
        iterator=int(gameBoard->Players.at(gameBoard->order)->MyProperties.size())-1;
    }

    listPrint();
}

bool my_Properties::ColorMortgaged(){

    for(int i=0;i<int(gameBoard->Properties.size());i++){


        if(gameBoard->Properties.at(i)->get_color()==gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_color()){

            if(gameBoard->Properties.at(i)->get_mortgaged()){
                return false;
            }

        }

    }
    return true;


}

bool my_Properties::EqualityCheck(int BuyOrSell){

  for(int i=0;i<int(gameBoard->Properties.size());i++){


     if(gameBoard->Properties.at(i)->get_color()==gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_color()){

         int difference=gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_number_of_houses()-gameBoard->Properties.at(i)->get_number_of_houses();

         if(difference!=0 && difference!=BuyOrSell){

             return false;

         }





     }



     }

      return true;



  }


bool my_Properties::MaxOrMinCheck(int BuyOrSell){



           if(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_number_of_houses()!=BuyOrSell){

               return false;


           }


    return true;
}




void my_Properties::on_pushButton_clicked()//buy house
{



   bool Monopoly=gameBoard->Monopoly(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_color(),gameBoard->Players.at(gameBoard->order));

   if(!MaxOrMinCheck(4)){

   if(Monopoly){


       if(ColorMortgaged()){

           if(EqualityCheck(-1)){

               gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->set_number_of_houses(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_number_of_houses()+1);

               gameBoard->Players.at(gameBoard->order)->set_Munny(gameBoard->Players.at(gameBoard->order)->get_Munny()- gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_house());
               gameBoard->print_order();

                QMessageBox::information(this,"Information","You bought a house for your property.");

                listPrint();

           }
           else{

               QMessageBox::warning(this,"Warning","You have to build houses equally.");

           }



       }
       else{


           QMessageBox::warning(this,"Warning","There are some mortgaged properties with this color.");

       }

   }
   else{

       QMessageBox::warning(this,"Warning","You do not own all "+QString::fromStdString(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_color())+" properties!");

   }

   }
   else{


      QMessageBox::warning(this,"Warning","You have 4 houses on this property,you can't buy more houses!");

   }


}

void my_Properties::on_pushButton_4_clicked()//sell house
{

    if(!MaxOrMinCheck(0)){

        if(EqualityCheck(1)){

            gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->set_number_of_houses(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_number_of_houses()-1);

            gameBoard->Players.at(gameBoard->order)->set_Munny(gameBoard->Players.at(gameBoard->order)->get_Munny()+0.5*(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_house()));

            gameBoard->print_order();

             QMessageBox::information(this,"Information","You sold one of the houses on this property.");

             listPrint();

        }
        else{

            QMessageBox::warning(this,"Warning","You have to sell houses equally.");

        }



    }
    else{

        QMessageBox::warning(this,"Warning","You don't have any houses on this property to sell!");

    }
}

void my_Properties::on_pushButton_2_clicked()//buy hotel
{
    bool FourOrFiveHouses=true;

    for(int i=0;i<int(gameBoard->Properties.size());i++){


       if(gameBoard->Properties.at(i)->get_color()==gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_color()){

           if(gameBoard->Properties.at(i)->get_number_of_houses()!=4 && gameBoard->Properties.at(i)->get_number_of_houses()!=5){

               FourOrFiveHouses=false;

           }

       }


    }


    if(FourOrFiveHouses==true){

        gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->set_number_of_houses(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_number_of_houses()+1);

        gameBoard->Players.at(gameBoard->order)->set_Munny(gameBoard->Players.at(gameBoard->order)->get_Munny()- gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_hotel());

        gameBoard->print_order();

         QMessageBox::information(this,"Information","You bought a hotel for your property.");


        listPrint();

    }
    else{

         QMessageBox::information(this,"Information","You need to have 4 houses or a hotel on the color group properties to buy a hotel.");
    }

}

void my_Properties::on_pushButton_5_clicked()//sell hotel
{

    if(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_number_of_houses()==5){

        gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->set_number_of_houses(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_number_of_houses()-1);

        gameBoard->Players.at(gameBoard->order)->set_Munny(gameBoard->Players.at(gameBoard->order)->get_Munny()+0.5*(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_hotel()));

        gameBoard->print_order();

         QMessageBox::information(this,"Information","You sold the hotel on this property.");

         listPrint();
    }
    else{

        QMessageBox::information(this,"Information","You don't own a hotel on this property.");
    }
}

void my_Properties::on_pushButton_7_clicked()//mortgage and un mortgage
{
    if(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_mortgaged()==false){

        gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->set_mortgage(true);

        gameBoard->Players.at(gameBoard->order)->set_Munny(gameBoard->Players.at(gameBoard->order)->get_Munny()+gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_mortgage());

        gameBoard->print_order();

        QMessageBox::information(this,"Information","This property is mortgaged now.");

        listPrint();

    }
    else{

         gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->set_mortgage(false);

         gameBoard->Players.at(gameBoard->order)->set_Munny(gameBoard->Players.at(gameBoard->order)->get_Munny()- 1.1*(gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_mortgage()));

         gameBoard->print_order();

         QMessageBox::information(this,"Information","This property is not mortgaged anymore.");

         listPrint();

    }

}

void my_Properties::on_pushButton_3_clicked()
{
    bool unimproved_properties=true;

    for(int i=0;i<int(gameBoard->Properties.size());i++){


        if(gameBoard->Properties.at(i)->get_color()==gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_color()){

            if(gameBoard->Properties.at(i)->get_number_of_houses()>0){

                unimproved_properties=false;

            }

        }

    }

    if(unimproved_properties ||gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_type()==RR || gameBoard->Players.at(gameBoard->order)->MyProperties.at(iterator)->get_type()==UTILITY_){

   sell_property * Sell_Property=new sell_property(iterator,this);

  int code=Sell_Property->exec();

    if(code==QDialog::Accepted){



        if(iterator==int(gameBoard->Players.at(gameBoard->order)->MyProperties.size())){

            iterator--;

        }






        listPrint();


    }



    }
    else{

        QMessageBox::information(this,"Information","There are some improved properties in this color group.");
    }

}
