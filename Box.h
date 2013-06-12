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

    Box(BBox &box) {
        real_box = box;

        xmat_i = mat4(1.0f);
        xmatT = mat4(1.0f);
    }

    void read(istream &in) {

        string property("");
        skip_to(in, '{');

        read_vec3(in, real_box.min);

        skip_to(in, ',');

        read_vec3(in, real_box.max);

        real_box.calcCenter();

        GeomObject::read(in);

        calcBBox();
    }

    void calcBBox() {

        box.min = real_box.min;
        box.max = real_box.max;
        box.center = real_box.center;

        box.transform_to_world(xmat_i);
    }

    Hit* intersect(const Ray &world_ray) {
        
        // ray is in object coordinates now
        Ray ray;
        world_ray.transform(ray, xmat_i);

        float t = real_box.intersect(ray);

        if (t > 0) {
            return new Hit(t, this);
        }

        return NULL;
    }

    vec3 getNormal(vec3 pos_world) {

        vec3 pos_obj = transformv3(pos_world, xmat_i);


        vec3 r = pos_obj - real_box.center;
        int biggest = 0; // x=0, y=1, z=2

        // find biggest coord
        if (abs(r.x) > abs(r.y)) {
            biggest = 0;
        } else {
            biggest = 1;
        }
        if (abs(r.z) > abs(r[biggest])) {
            biggest = 2;
        }
        
        vec3 norm_obj(0.0f);
        norm_obj[biggest] = r[biggest];

        return glm::normalize(transformv3_normal(norm_obj, xmatT));
    }


    void print_properties() {
        print3f(real_box.min, "corner1");
        print3f(real_box.max, "corner2");

        print3f(box.min, "bbox min");
        print3f(box.max, "bbox max");

        GeomObject::print_properties();


    }

    BBox real_box;
};

#endif
