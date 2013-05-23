#ifndef BBOX_H
#define BBOX_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"
#include "Ray.h"

using std::string;
using glm::vec3;


class BBox {

public:

    BBox() {
        corner1 = vec3(0.0);
        corner2 = vec3(0.0);
    }

    BBox(vec3 min, vec3 max) {
        this->corner1 = min;
        this->corner2 = max;
        calcCenter();
    }

    void calcCenter() {
        center = vec3(0.5) * (corner1 + corner2);
    }

    void read(istream &in) {
        /*

        char dummy;
        string property("");
        skip_to(in, '{');

        read_vec3(in, corner1);

        skip_to(in, ',');

        read_vec3(in, corner2);

        GeomObject::read(in);
        */
    }

    void print_properties() {
        print3f(corner1, "corner1");
        print3f(corner2, "corner2");
    }

    float intersect(const Ray &world_ray) {

        vec3 min = corner1;
        vec3 max = corner2;
        
        float t0=0.0f;
        float t1=1.0/0.0f;

        // from Physically Based Rendering 4.2.1
        for (int i=0; i < 3; i++) {
            float oneOverD = 1.0f / world_ray.d[i];
            float tmin = (min[i] - world_ray.p0[i]) * oneOverD;
            float tmax = (max[i] - world_ray.p0[i]) * oneOverD;

            if (tmin > tmax) {
                float tmp = tmax;
                tmax = tmin;
                tmin = tmp;
            }
            t0 = tmin > t0 ? tmin : t0;
            t1 = tmax < t1 ? tmax : t1;

            if (t0 > t1) {
                return 0;
            }
        }

        return get_least_positive(t0, t2);
    }

    float get_least_positive(t1, t2) {
        if (t1 > 0 && t2 > 0) {
            min(t1, t2);
        } else if (t1 > 0) {
            return t1;
        } else if (t2 > 0) {
            return t2;
        } else {
            return 0;
        }
    }

    BBox operator+(const BBox &other) const {

        BBox result;

        result.corner1.x = min(corner1.x, other.corner1.x);
        result.corner1.y = min(corner1.y, other.corner1.y);
        result.corner1.z = min(corner1.z, other.corner1.z);

        result.corner2.x = max(corner2.x, other.corner2.x);
        result.corner2.y = max(corner2.y, other.corner2.y);
        result.corner2.z = max(corner2.z, other.corner2.z);

        result.calcCenter();

        return result;
    }

    vec3 corner1; // min
    vec3 corner2; // max
    vec3 center;
};

#endif
