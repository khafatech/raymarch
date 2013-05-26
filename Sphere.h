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


    Hit* intersect(const Ray &world_ray) {

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
            sqrt_delta = sqrt(delta);
            t1 = (-dot(ray.d, e_min_c) + sqrt_delta) / dd;
            t2 = (-dot(ray.d, e_min_c) - sqrt_delta) / dd;


            // return leaset positive t
            if (t1 > 0 && t2 > 0) {
                return new Hit(min(t1, t2), this);
            } else if (t1 > 0) {
                return new Hit(t1, this);
            } else if (t2 > 0) {
                return new Hit(t2, this);
            } else {
                return NULL;
            }

        } else {
            // no intersection
            return NULL;
        }
    }




    vec3 getNormal(vec3 pos_world) {

        vec3 pos_obj = transformv3(pos_world, xmat_i);

        vec3 norm_obj = glm::normalize(pos_obj - location);

        return glm::normalize(transformv3_normal(norm_obj, xmatT));
    }

    void read(istream &in) {

        string property("");

        skip_to(in, '{');
        // cout << "read '" << dummy << "'\n";

        read_vec3(in, location);

        skip_to(in, ',');

        in >> radius;

        GeomObject::read(in);

        calcBBox();
    }

    void calcBBox() {

        // obj bbox
        box.center = location;
        box.corner1 = vec3(-radius) + location;
        box.corner2 = vec3(radius) + location;


        // TODO - put in function
        vector<vec4> box_points;
        mat4 xmat = glm::inverse(xmat_i);
        box.get_points(box_points);

        // transform points to world
        for (int i=0; i < (int) box_points.size(); i++) {
            box_points[i] = xmat * box_points[i];
        }

        // find new box that fits transformed box
        vec3 min = vec4_to_vec3(box_points[0]);
        vec3 max = vec4_to_vec3(box_points[1]);
        for (int i=0; i < (int) box_points.size(); i++) {
            if (box_points[i].x < min.x) {
                min.x = box_points[i].x;
            }
            if (box_points[i].y < min.y) {
                min.y = box_points[i].y;
            }
            if (box_points[i].z < min.z) {
                min.z = box_points[i].z;
            }

            if (box_points[i].x > max.x) {
                max.x = box_points[i].x;
            }
            if (box_points[i].y > max.y) {
                max.y = box_points[i].y;
            }
            if (box_points[i].z > max.z) {
                max.z = box_points[i].z;
            }
        }

        box.corner1 = min;
        box.corner2 = max;
        box.calcCenter();
    }

    void print_properties() {
        cout << "radius: " << radius << endl;
        GeomObject::print_properties();
    }

    float radius;
};

#endif
