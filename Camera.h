#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"

using glm::vec3;
using std::string;



class Camera : public BaseObject {

public:

    Camera() {
        name = "camera";
    }

    void read(istream &in) {

        char dummy;
        string property;

        skip_to(in, '{');
        // cout << "read '" << dummy << "'\n";

        while (property != "}") {
            in >> property;

            // cout << "read '" << property << "'\n";

            if (property == "location") {
                read_vec3(in, location);
            } else if (property == "up") {
                read_vec3(in, up);
            } else if (property == "right") {
                read_vec3(in, right);
            } else if (property == "look_at") {
                read_vec3(in, look_at);
            }
        }
    }

    void print_properties() {
        print3f(location, "loc");
        print3f(up, "up");
        print3f(right, "right");
        print3f(up, "look_at");
    }

    vec3 up;
    vec3 right;
    vec3 look_at;
};

#endif
