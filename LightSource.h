#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"


using glm::vec3;
using std::string;


class LightSource : public BaseObject {

public:

    LightSource() {
        name = "light_source";
    }

    void read(istream &in) {

        string dummy;

        skip_to(in, '{');

        read_vec3(in, location);

        in >> dummy;
        in >> dummy;
        
        read_vec3(in, color);
        skip_to(in, '}');

    }

    void print_properties() {
        print3f(location, "loc");
        print3f(color, "color");
    }

    vec3 color;
};


#endif
