#ifndef BOX_H
#define BOX_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"
#include "GeomObj.h"

#include "BBox.h"

using std::string;



class Box : public GeomObject {

public:

    Box() {
        name = "box";
    }

    void read(istream &in) {

        string property("");
        skip_to(in, '{');

        read_vec3(in, corner1);

        skip_to(in, ',');

        read_vec3(in, corner2);

        GeomObject::read(in);
    }

    void print_properties() {
        print3f(corner1, "corner1");
        print3f(corner2, "corner2");
        GeomObject::print_properties();
    }

    vec3 corner1;
    vec3 corner2;
};

#endif
