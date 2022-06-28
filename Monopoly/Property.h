#ifndef PROPERTY_H
#define PROPERTY_H
#include <QLabel>
#include <string>
#include <Player.h>

using std::string;

enum Type{GO,PROPERTY,COMMUNITY,CHANCE,INCOMETAX,LUXURYTAX,JAIL,PARKING,GOTOJAIL};


class Property{

   private:

    Type type;


    //baraye sanad ha
    //pathe carte malekiat


    string PropertyCard;

    int price;

    int rent0;

    int rent1;

    int rent2;

    int rent3;

    int rent4;

    int rentHotel;

    int mortgage;

    int house;

    int hotel;

    int number_of_houses;

    bool mortgaged;

    string color;

    //Railroad

    int rent;

    //Utility

    int multiplier1;

    int multiplier2;



    public:

    QLabel * PropertyOnTheBoard;

    Player * owner;

    //constructor baraye 4 gooshe
    Property(Type);


    //constructor baraye property ha

    Property(Type,string,int,int,int,int,int,int,int,int,int,int,int,bool,string);

    //constructor baraye Railroad

    Property(Type,string,int,int,int,bool,string);


    //constructor baraye Utility

    Property(Type,string,int,int,int,int,bool,string);


    void set_number_of_houses(int number_of_houses);

    void set_mortgage(bool);


    Type get_type() const;

    string get_PropertyCard() const;

    int get_price() const;

    int get_rent0() const;

    int get_rent1()const;

    int get_rent2()const;

    int get_rent3() const;

    int get_rent4() const;

    int get_rentHotel() const;

    int get_mortgage() const;

    int get_house() const;

    int get_hotel() const;

    int get_number_of_houses() const;

    bool get_mortgaged() const;

    string get_color() const;

    int get_rent() const;

    int get_multiplier1() const;

    int get_multiplier2() const;


};








#endif // PROPERTY_H
