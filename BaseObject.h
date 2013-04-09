
#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include <iostream>
#include <string>

using std::string;
using std::istream;

class BaseObject {


public:
    
    virtual void read(istream &) = 0;
    
    virtual void print_properties() = 0;
    
    vec3 location;

    string name;
    
};

#endif
