#include "gameboard.h"
#include "ui_gameboard.h"
#include <QDebug>



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

GameBoard::GameBoard(QWidget *parent,int number_of_players) :
    QDialog(parent),
    ui(new Ui::GameBoard),
    number_of_players(number_of_players)
{

    ui->setupUi(this);



   //vared kardane path va function kart haye shans








    Randomizer(ChanceCards);

    Randomizer(CommunityCards);



    //por shavad token path ha

    Randomizer(tokens_path);





    for(int i=0;i<number_of_players;i++){

        //sakhtane Player * va dadan be vector


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
GameBoard * GameBoard::get_instance(QWidget *parent,int number_of_players){

    if(instance==nullptr){

        instance=new GameBoard(parent,number_of_players);


    }

     return instance;




}

GameBoard::~GameBoard()
{
    delete ui;


}
