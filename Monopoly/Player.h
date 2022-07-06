#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <QLabel>
class Property;


using std::string;

using std::vector;


class Player{

private:




    string nickname;//esm player

    long int Munny;//pul player

    bool get_out_of_jail;//dashtn ya nadashtn cart khoroj az zendan

    int position;//mogheiat dar board



public:

    Player(string,QLabel *);

    ~Player();

    QLabel* token;//mohre

    void set_Munny(long int);

    void set_jail(bool);

    void set_position(int);

    long int get_Munny() const;

    bool get_jail() const;

    int get_position() const;

    string get_nickname() const;


    vector<Property*> MyProperties;//vector amlak

    string tokenPath;//addres aks mohre

   int number_of_turns_in_jail;//tedad bary ke to zendadn bode


};






#endif // PLAYER_H
