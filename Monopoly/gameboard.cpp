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

bool throwDice(int &Dice1,int &Dice2){
    Dice1=rand() % 6 + 1;

    Dice2=rand() % 6 + 1;


    if(Dice1==Dice2){
        return true;
    }
    else{
        return false;
    }
}


GameBoard * GameBoard::instance=nullptr;

GameBoard::GameBoard(vector<string> nicknames,QWidget *parent,int number_of_players) :
    QDialog(parent),
    ui(new Ui::GameBoard),
    number_of_players(number_of_players)

{

    ui->setupUi(this);



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



    //por shavad token path ha

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
