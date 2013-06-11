#ifndef BBOX_H
#define BBOX_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"
#include "Ray.h"

#include <vector>

using std::string;
using std::vector;
using glm::vec3;
using glm::vec4;


class BBox {

public:

    BBox() {
        min = vec3(0.0);
        max = vec3(0.0);
    }

    BBox(vec3 min, vec3 max) {
        this->min = min;
        this->max = max;
        calcCenter();
    }

    void calcCenter() {
        center = vec3(0.5) * (min + max);
    }

    void read(istream &in) {
        /*

        char dummy;
        string property("");
        skip_to(in, '{');

        read_vec3(in, min);

        skip_to(in, ',');

        read_vec3(in, max);

        GeomObject::read(in);
        */
    }

    void print_properties() {
        print3f(min, "min");
        print3f(max, "max");
    }

    float intersect(const Ray &world_ray) {

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

        // return intersection point closer to ray origin.
        // return  Max(t0, 0); // get_least_positive(t0, t1);
        // FIXME - doesn't return the real t
        return 1;
    }

    float get_least_positive(float t1, float t2) {
        if (t1 > 0 && t2 > 0) {
            Min(t1, t2);
        } else if (t1 > 0) {
            return t1;
        } else if (t2 > 0) {
            return t2;
        } 
        // FIXME - doesn't return the real t
        return 1;
    }

    BBox operator+(const BBox &other) const {

        BBox result;

        result.min.x = Min(min.x, other.min.x);
        result.min.y = Min(min.y, other.min.y);
        result.min.z = Min(min.z, other.min.z);

        result.max.x = Max(max.x, other.max.x);
        result.max.y = Max(max.y, other.max.y);
        result.max.z = Max(max.z, other.max.z);

        result.calcCenter();

        return result;
    }

    void get_points(vector<vec4> &points) {
        points.push_back(vec4(min.x, min.y, min.z, 1));
        points.push_back(vec4(max.x, max.y, max.z, 1));
        points.push_back(vec4(min.x, max.y, min.z, 1));
        points.push_back(vec4(min.x, max.y, max.z, 1));
        points.push_back(vec4(max.x, max.y, min.z, 1));
        points.push_back(vec4(max.x, min.y, min.z, 1));
        points.push_back(vec4(max.x, min.y, max.z, 1));
        points.push_back(vec4(min.x, min.y, max.z, 1));
    }

    
    // transforms points and creates a new Axis-aligned BBox
    void transform_to_world(const mat4 xmat_i) {
        vector<vec4> box_points;
        mat4 xmat = glm::inverse(xmat_i);

        get_points(box_points);

        // transform points to world
        for (int i=0; i < (int) box_points.size(); i++) {
            box_points[i] = xmat * box_points[i];
        }

        boundPoints(box_points);
    }

    void boundPoints(const vector<vec4> &points) {

        // find new box that fits transformed box
        min = vec4_to_vec3(points[0]);
        max = vec4_to_vec3(points[1]);
        for (int i=0; i < (int) points.size(); i++) {
            if (points[i].x < min.x) {
                min.x = points[i].x;
            }
            if (points[i].y < min.y) {
                min.y = points[i].y;
            }
            if (points[i].z < min.z) {
                min.z = points[i].z;
            }

            if (points[i].x > max.x) {
                max.x = points[i].x;
            }
            if (points[i].y > max.y) {
                max.y = points[i].y;
            }
            if (points[i].z > max.z) {
                max.z = points[i].z;
            }
        }

        calcCenter();
    }

    vec3 min; // min
    vec3 max; // max
    vec3 center;
};

#endif
