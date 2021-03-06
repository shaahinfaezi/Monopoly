
#include "Property.h"



//constructor baraye 4 gooshe va chance va community
Property::Property(QLabel*PropertyOnTheBoard,Type type){

    this->PropertyOnTheBoard=PropertyOnTheBoard;

    this->type=type;
}


//constructor baraye property ha

Property::Property(QLabel* PropertyOnTheBoard,Type type,

string PropertyCard,

int price,

int rent0,

int rent1,

int rent2,

int rent3,

int rent4,

int rentHotel,

int mortgage,

int house,

int hotel,

string color){

    this->PropertyOnTheBoard=PropertyOnTheBoard;

    this->type=type;

    this->PropertyCard=PropertyCard;

    this->price=price;

    this->rent0=rent0;

    this->rent1=rent1;

    this->rent2=rent2;

    this->rent3=rent3;

    this->rent4=rent4;

    this->rentHotel=rentHotel;

    this->mortgage=mortgage;

    this->house=house;

    this->hotel=hotel;

    this->number_of_houses=0;

    this->mortgaged=false;

    this->color=color;

    owner=nullptr;




}

//constructor baraye Railroad

Property::Property(QLabel* PropertyOnTheBoard,Type type,

                   string PropertyCard,

                   int price,

                   int rent1,

                   int rent2,

                   int rent3,

                   int rent4,

                   int mortgage,

                   string color){

    this->PropertyOnTheBoard=PropertyOnTheBoard;

    this->type=type;

    this->PropertyCard=PropertyCard;

    this->price=price;

    this->rent1=rent1;

    this->rent2=rent2;

    this->rent3=rent3;

    this->rent4=rent4;

    this->mortgage=mortgage;

    this->mortgaged=false;

    this->color=color;

    owner=nullptr;


}


//constructor baraye Utility

Property::Property(QLabel* PropertyOnTheBoard,Type type,

                   string PropertyCard,

                   int price,

                   int multiplier1,

                   int multiplier2,

                   int mortgage,

                   string color){

    this->PropertyOnTheBoard=PropertyOnTheBoard;

    this->type=type;

    this->PropertyCard=PropertyCard;

    this->price=price;

    this->multiplier1=multiplier1;

    this->multiplier2=multiplier2;

    this->mortgage=mortgage;

    this->mortgaged=false;

    this->color=color;

    owner=nullptr;
}


void Property::set_number_of_houses(int number_of_houses){

      this->number_of_houses=number_of_houses;

}

void Property::set_mortgage(bool mortgaged){

    this->mortgaged=mortgaged;


}


Type Property::get_type() const{

    return type;
}

string Property::get_PropertyCard() const{

    return PropertyCard;


}

int Property::get_price() const{


    return price;

}

int Property::get_rent0() const{


    return rent0;
}

int Property::get_rent1()const{

    return rent1;
}

int Property::get_rent2()const{

    return rent2;

}

int Property::get_rent3() const{

    return rent3;

}

int Property::get_rent4() const{

    return rent4;

}

int Property::get_rentHotel() const{

    return rentHotel;


}

int Property::get_mortgage() const{


    return mortgage;

}

int Property::get_house() const{

    return house;


}

int Property::get_hotel() const{

    return hotel;

}

int Property::get_number_of_houses() const{

    return number_of_houses;


}

bool Property::get_mortgaged() const{

    return mortgaged;


}

string Property::get_color() const{

    return color;

}

int Property::get_rent() const{

    return rent;

}

int Property::get_multiplier1() const{


    return  multiplier1;

}

int Property::get_multiplier2() const{

    return multiplier2;
}





