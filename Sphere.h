#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"
#include "GeomObj.h"

using std::string;



class Sphere : public GeomObject {

public:

    Sphere() {
        name = "sphere";
    }

    void read(istream &in) {

        char dummy;
        string property;

        skip_to(in, '{');
        // cout << "read '" << dummy << "'\n";

        read_vec3(in, location);

        skip_to(in, ',');

        in >> radius;

        while (property != "}") {
            in >> property;

            if (property == "pigment") {
            } else if (property == "finish") {
            } else if (property == "translate") {
                read_vec3(in, translate);
            }
        }
    }

    void print_properties() {
        // TODO print all properties
        cout << "radius: " << radius << endl;
    }

    float radius;
};

#endif
