#ifndef SPHERE_H
#define SPHERE_H

#include <string>
#include <math.h>

#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"
#include "GeomObj.h"

using std::string;


using glm::dot;

#define sqvec(v) dot((v), (v))


class Sphere : public GeomObject {

public:

    Sphere() {
        name = "sphere";
    }


    float intersect(const Ray &world_ray) {

        /*
        cout << "ray:\n";
        ray.print();
        cout << endl;
        */

        Ray ray;

        // ray is in object coordinates now
        world_ray.transform(ray, xmat_i);

        float t1, t2;
        vec3 e_min_c = ray.p0 - location;
        float dd = sqvec(ray.d);
        float sqrt_delta;

        float delta = POWER2(dot(ray.d, e_min_c))
         - dd * (sqvec(e_min_c) - POWER2(radius));


        if (delta >= 0) {
            dprint("delta > 0\n");
            
            sqrt_delta = sqrt(delta);
            t1 = (-dot(ray.d, e_min_c) + sqrt_delta) / dd;
            t2 = (-dot(ray.d, e_min_c) - sqrt_delta) / dd;

            // debug
            /*
            cout << "t1: " << t1 << endl;
            cout << "t2: " << t2 << endl;
            */

            

            return MIN(t1, t2);

        } else {
            // no intersection
            return 0;
        }
    }


#define vec4_to_vec3(v4) vec3(v4.x, v4.y, v4.z)

    vec3 transformv3(vec3 v, mat4 mat) {
        vec3 result;
        vec4 result4;

        vec4 v4 = vec4(v.x, v.y, v.z, 1.0);

        result4 = mat * v4;

        result = vec4_to_vec3(result4);

        return result;
    }

    vec3 transformv3_normal(vec3 v, mat4 mat) {
        vec3 result;
        vec4 result4;

        vec4 v4 = vec4(v.x, v.y, v.z, 0.0);

        result4 = mat * v4;

        result = vec4_to_vec3(result4);

        return result;
    }

    vec3 getNormal(vec3 pos_world) {

        vec3 pos_obj = transformv3(pos_world, xmat_i);

        vec3 norm_obj = glm::normalize(pos_obj - location);

        // print3f(norm_obj, "norm_obj");

        return glm::normalize(transformv3_normal(norm_obj, xmatT));
        // return norm_obj;
    }

    void read(istream &in) {

        char dummy;
        string property("");

        skip_to(in, '{');
        // cout << "read '" << dummy << "'\n";

        read_vec3(in, location);

        skip_to(in, ',');

        in >> radius;

        GeomObject::read(in);
    }

    void print_properties() {
        cout << "radius: " << radius << endl;
        GeomObject::print_properties();
    }

    float radius;
};

#endif
