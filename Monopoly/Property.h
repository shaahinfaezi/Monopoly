 #ifndef PROPERTY_H
#define PROPERTY_H
#include <QLabel>
#include <string>
class Player;
#include <vector>

using std::vector;

using std::string;

enum Type{GO__,PROPERTY,COMMUNITY,CHANCE,INCOMETAX,LUXURYTAX,JAIL,PARKING,GOTOJAIL,RR,UTILITY_};


class Property{

   private:

    Type type;//noe khone dar safe


    //baraye sanad ha
    //pathe carte malekiat


    string PropertyCard;

    int price;//gheimat khone

    int rent0;

    int rent1;

    int rent2;

    int rent3;

    int rent4;

    int rentHotel;

    int mortgage;

    int house;//gheimat har khone

    int hotel;//gheimat har hotel

    int number_of_houses;

    bool mortgaged;//rahn dade shode ya na

    string color;

    //Railroad

    int rent;

    //Utility

    int multiplier1;//4

    int multiplier2;//10



    public:

    QLabel * PropertyOnTheBoard;//melk dar board

    Player * owner;

    vector<Player *> PlayersOnProperty;//player hay ke ro har khone

    //constructor baraye 4 gooshe va community va chance
    Property(QLabel*,Type);


    //constructor baraye property ha

    Property(QLabel*,Type,string,int,int,int,int,int,int,int,int,int,int,string);

    //constructor baraye Railroad

    Property(QLabel*,Type,string,int,int,int,int,int,int,string);


    //constructor baraye Utility

    Property(QLabel*,Type,string,int,int,int,int,string);


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
