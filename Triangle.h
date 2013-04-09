#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"
#include "GeomObj.h"

using std::string;



class Triangle : public GeomObject {

public:

    Triangle() {
        name = "triangle";
    }

    void read(istream &in) {

        char dummy;
        string property("");
        skip_to(in, '{');

        read_vec3(in, c1);
        skip_to(in, ',');
        read_vec3(in, c2);
        skip_to(in, ',');
        read_vec3(in, c3);

        GeomObject::read(in);
    }

    void print_properties() {
        print3f(c1, "corner1");
        print3f(c2, "corner2");
        print3f(c3, "corner3");
        GeomObject::print_properties();
    }

    vec3 c1;
    vec3 c2;
    vec3 c3;
};

#endif
