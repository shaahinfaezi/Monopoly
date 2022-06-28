#include "Player.h"


Player::Player(string nickname,QLabel * token):nickname(nickname),Munny(1500),get_out_of_jail(false),position(-1){


this->token=token;



}



Player::~Player(){




}


void Player::set_Munny(long int Munny){

    this->Munny=Munny;

}

void Player::set_jail(bool get_out_of_jail){

    this->get_out_of_jail=get_out_of_jail;


}

void Player::set_position(int position){

    this->position=position;

}

long int Player::get_Munny() const{

    return Munny;
}

bool Player::get_jail() const{

    return get_out_of_jail;


}

int Player::get_position() const{

    return position;

}

string Player::get_nickname() const{

    return nickname;

}
