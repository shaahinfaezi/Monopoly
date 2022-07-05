#ifndef COMMUNITY_H
#define COMMUNITY_H


#include <string>

using std::string;

//kary ke to kart gofte anjam mide

enum Function_{GO_,BANK200,DOCTOR50,STOCK45,FIFTY_FROM_EVERYONE,GETOUT_,JAIL_NO_GO_,TAX20,INSURANCE100,HOSPITAL100,SCHOOL150,SERVICE25,XMAS100,REPAIRS_,BEAUTY20,INHERIT100};

class Community{

private:

     string path;

     Function_ function;

public:

     Community(){};

     ~Community(){};

     void set_path(string);

     void set_function(Function_);

     string get_path() const;

     Function_ get_function() const;


};






#endif // COMMUNITY_H
