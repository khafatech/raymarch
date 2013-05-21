#ifndef BBOX_H
#define BBOX_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"
#include "GeomObj.h"

using std::string;



class BBox : public GeomObject {

public:

    BBox() {
        name = "bbox";
    }

    BBox(vec3 min, vec3 max) {
        name = "bbox";
        this->corner1 = min;
        this->corner2 = max;
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
        GeomObject::print_properties();
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

        return 1;
    }

    vec3 corner1; // min
    vec3 corner2; // max
};

#endif
