#include "Chance.h"


void Chance::set_path(string path){


    this->path=path;
}

void Chance::set_function(Function function){

    this->function=function;

}

string Chance::get_path() const{

    return path;

}

Function Chance::get_function() const{


    return  function;

}
