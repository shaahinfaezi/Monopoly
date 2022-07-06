#include "Community.h"


void Community::set_path(string path){


    this->path=path;
}

void Community::set_function(Function_ function){

    this->function=function;

}

string Community::get_path() const{

    return path;

}

Function_ Community::get_function() const{


    return  function;

}
