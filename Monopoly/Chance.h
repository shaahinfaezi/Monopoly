#ifndef CHANCE_H
#define CHANCE_H

#include <string>

using std::string;

enum Function{A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16};

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
