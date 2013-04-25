#ifndef RAY_H
#define RAY_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"

using std::string;


using glm::mat4;


class Ray {

public:

    Ray() {
        p0 = vec3(0.0);
        d = vec3(0.0);
    }

    // returns the transformed ray. Doesn't edit ray
    void transform(Ray &new_ray, glm::mat4 mat) const {
        vec4 new_p0 = mat * vec4(p0.x, p0.y, p0.z, 1.0);
        vec4 new_d = mat * vec4(d.x, d.y, d.z, 0.0);;

        new_ray.p0 = vec3(new_p0.x, new_p0.y, new_p0.z);
        new_ray.d = vec3(new_d.x, new_d.y, new_d.z);
    }

    Ray& operator=(const Ray& ray) {
        p0 = ray.p0;
        d = ray.d;
        return *this;
    }

    void print() const {
        print3f(p0, "p0");
        print3f(d, "d");
    }

    vec3 p0; // point
    vec3 d;  // direction
};

#endif
