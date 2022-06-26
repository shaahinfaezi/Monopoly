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

    void print();

private:
    Ui::GameBoard *ui;

    int number_of_players;

    explicit GameBoard(vector<string>,QWidget *parent = nullptr,int=2);

    static GameBoard * instance;

    vector<Chance*> ChanceCards;

    vector<Community*> CommunityCards;

    vector<string> tokens_path;

    vector<Player*> Players;
};

#endif // GAMEBOARD_H
