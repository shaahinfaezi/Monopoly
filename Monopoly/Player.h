#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <QLabel>
#include <Property.h>


using std::string;

using std::vector;


class Player{

private:


    vector<Property*> Properties;

    string nickname;

    long int Munny;

    bool get_out_of_jail;

    int position;



public:

    Player(string,QLabel *);

    ~Player();

    QLabel* token;

    void set_Munny(long int);

    void set_jail(bool);

    void set_position(int);

    long int get_Munny() const;

    bool get_jail() const;

    int get_position() const;

    string get_nickname() const;
















};






#endif // PLAYER_H
