#ifndef PLANE_H
#define PLANE_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"
#include "GeomObj.h"

using std::string;



class Plane : public GeomObject {

public:

    Plane() {
        name = "plane";
    }

    void read(istream &in) {

        char dummy;
        string property("");

        skip_to(in, '{');
        // cout << "read '" << dummy << "'\n";

        read_vec3(in, location);

        skip_to(in, ',');

        in >> distance;

        GeomObject::read(in);
    }

    void print_properties() {
        cout << "distance: " << distance << endl;
        GeomObject::print_properties();
    }

    float distance;
};

#endif
