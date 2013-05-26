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

        return get_least_positive(t0, t1);
    }

    float get_least_positive(float t1, float t2) {
        if (t1 > 0 && t2 > 0) {
            min(t1, t2);
        } else if (t1 > 0) {
            return t1;
        } else if (t2 > 0) {
            return t2;
        } 
        return 1;
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

    void get_points(vector<vec4> &points) {
        points.push_back(vec4(corner1.x, corner1.y, corner1.z, 1));
        points.push_back(vec4(corner2.x, corner2.y, corner2.z, 1));
        points.push_back(vec4(corner1.x, corner2.y, corner1.z, 1));
        points.push_back(vec4(corner1.x, corner2.y, corner2.z, 1));
        points.push_back(vec4(corner2.x, corner2.y, corner1.z, 1));
        points.push_back(vec4(corner2.x, corner1.y, corner1.z, 1));
        points.push_back(vec4(corner2.x, corner1.y, corner2.z, 1));
        points.push_back(vec4(corner1.x, corner1.y, corner2.z, 1));
    }
    
    // transforms points and creates a new Axis-aligned BBox
    void transform_to_world(mat4 xmat_i) {
        vector<vec4> box_points;
        mat4 xmat = glm::inverse(xmat_i);

        get_points(box_points);

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

        corner1 = min;
        corner2 = max;
        calcCenter();
    }

    vec3 corner1; // min
    vec3 corner2; // max
    vec3 center;
};

#endif
