
#ifndef GEOM_OBJECT_H
#define GEOM_OBJECT_H

#include <iostream>
#include <string>

#include "util.h"

using std::string;
using std::istream;
using glm::vec3;
using glm::vec4;


struct Pigment {

    Pigment() {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }

    void read(istream &in) {

        string dummy;
        skip_to(in, '{');

        in >> dummy;
        in >> dummy;

        if (dummy.size() == 4) {
            // rgbf
            read_vec4(in, color);
        } else {
            // rgb
            vec3 color3;
            read_vec3(in, color3);

            color.x = color3.x;
            color.y = color3.y;
            color.z = color3.z;
            color.w = 1.0;
        }
        skip_to(in, '}');
    }

    vec4 color;
};



struct Finish {
    void read(istream &in) {
    }
};



class GeomObject : public BaseObject {

public:
    
    virtual void read(istream &) = 0;
    
    virtual void print_properties() = 0;

    
    Pigment pigment;
    Finish finish;
    vec3 translate;

};

#endif
