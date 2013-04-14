#ifndef RAY_H
#define RAY_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"

using std::string;



class Ray {

public:

    Ray() {
        p0 = vec3(0.0);
        d = vec3(0.0);
    }

    void print() {
        print3f(p0, "p0");
        print3f(d, "d");
    }

    vec3 p0; // point
    vec3 d;  // direction
};

#endif
