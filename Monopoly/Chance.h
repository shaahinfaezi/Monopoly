#ifndef CHANCE_H
#define CHANCE_H

#include <string>

using std::string;

enum Function{BOARDWALK,GO,ILLINOIS,ST_CHARLES_GO,RAILROAD,UTILIY,DIVIDEND,THREE_SPACES,GETOUT,JAIL_NO_GO,REPAIRS,POORTAX,READING_GO,ONE_FIFTY,FIFTY_FOR_EVERYONE,RAILROAD2};

class Chance{

private:

     string path;

     Function function;

public:

     Chance(){};

     ~Chance(){};

     void set_path(string);

     void set_function(Function);

     string get_path() const;

     Function get_function() const;


};




#endif // CHANCE_H
