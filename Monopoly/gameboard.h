#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QDialog>
#include "Chance.h"
#include "Community.h"
#include "Player.h"
#include "vector"

using std::vector;

namespace Ui {
class GameBoard;
}

class GameBoard : public QDialog
{
    Q_OBJECT

public:

    static GameBoard * get_instance(vector<string> nicknames={},QWidget *parent = nullptr,int=2);

    vector<Player*> Players;

    vector<Property *> Properties;

        int order;

         void print_order();

         void HideBuyButton();

    ~GameBoard();

    private slots:


     void on_pushButton_4_clicked();

     void on_pushButton_2_clicked();

         void movement();

          void clearDice();





          void on_pushButton_3_clicked();

          void on_pushButton_5_clicked();

          void on_pushButton_6_clicked();

          void on_pushButton_7_clicked();

          void on_pushButton_8_clicked();

private:
    Ui::GameBoard *ui;

    int number_of_players;

    explicit GameBoard(vector<string>,QWidget *parent = nullptr,int=2);

    static GameBoard * instance;

    vector<Chance*> ChanceCards;

    vector<Community*> CommunityCards;

    vector<string> tokens_path;



    bool throwDice(int &,int &);



    void printDice(int,int);

    vector<string> Dice_path;



    int Dice1,Dice2;

    int sums[8];

    int position;




    void set_position(int);

    void RenderMovement(int);

    bool Double;

    int Doubles;

    void PassGo();

    bool Monopoly(string,string);

    void jail();

    void SituationCheck();

    bool JailCheck;

    void rollDice();





};

#endif // GAMEBOARD_H
