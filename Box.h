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

        read_vec3(in, bbox.min);

        skip_to(in, ',');

        read_vec3(in, bbox.max);

        GeomObject::read(in);
    }

    Hit* intersect(const Ray &world_ray) {
        
        // ray is in object coordinates now
        Ray ray;
        world_ray.transform(ray, xmat_i);

        float t = bbox.intersect(ray);

        if (t > 0) {
            return new Hit(t, this);
        }

        return NULL;
    }

    void print_properties() {
        print3f(bbox.min, "corner1");
        print3f(bbox.max, "corner2");
        GeomObject::print_properties();
    }


    BBox bbox;

};

#endif
