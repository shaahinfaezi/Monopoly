#ifndef COMMUNITY_H
#define COMMUNITY_H


#include <string>

using std::string;

enum Function_{B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15,B16};

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
