#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <QLabel>


using std::string;

using std::vector;


class Player{

private:


    //vectori az amlak



    long int Munny;

    bool get_out_of_jail;

    QLabel* token;

    string nickname;



public:

    Player(string,QLabel *);

    ~Player();












};






#endif // PLAYER_H
