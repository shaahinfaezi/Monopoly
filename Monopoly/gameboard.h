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

    static GameBoard * get_instance(vector<string>,QWidget *parent = nullptr,int=2);

    ~GameBoard();

    private slots:


     void on_pushButton_4_clicked();

     void on_pushButton_2_clicked();

         void movement();



private:
    Ui::GameBoard *ui;

    int number_of_players;

    explicit GameBoard(vector<string>,QWidget *parent = nullptr,int=2);

    static GameBoard * instance;

    vector<Chance*> ChanceCards;

    vector<Community*> CommunityCards;

    vector<string> tokens_path;

    vector<Player*> Players;

    bool throwDice(int &,int &);

    void print_order();

    void printDice(int,int);

    vector<string> Dice_path;

    int order;

     int Dice1,Dice2;

      int sums[8];



    int position;

      vector<Property *> Properties;




};

#endif // GAMEBOARD_H
