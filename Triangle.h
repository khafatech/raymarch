#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"
#include "GeomObj.h"

using std::string;



class Triangle : public GeomObject {

public:

    Triangle() {
        name = "triangle";
    }

    void read(istream &in) {

        char dummy;
        string property("");
        skip_to(in, '{');

        read_vec3(in, c1);
        skip_to(in, ',');
        read_vec3(in, c2);
        skip_to(in, ',');
        read_vec3(in, c3);

        GeomObject::read(in);
    }

    void print_properties() {
        print3f(c1, "corner1");
        print3f(c2, "corner2");
        print3f(c3, "corner3");
        GeomObject::print_properties();
    }


    void array2mat3(glm::mat3 &m, float nums[3*3]) {
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m[j][i] = nums[i*3 + j];
            }
        }
    }

    virtual float intersect(const Ray &world_ray) {

        Ray ray;

        world_ray.transform(ray, xmat_i);

        // baycentric coords equations from Shirley book sec 10.3
        
        glm::mat3 A; // not for alpha. the matrix in denomenator
        glm::mat3 B; // beta
        glm::mat3 G; // gamma
        glm::mat3 T; // for t

        vec3 a = c1;
        vec3 b = c2;
        vec3 c = c3;
/*
#define a c1
#define b c2
#define c c3
*/

        float A_arr[] = {
                   a.x - b.x, a.x - c.x, ray.d.x,
                   a.y - b.y, a.y - c.y, ray.d.y,
                   a.z - b.z, a.z - c.z, ray.d.z,
                };

        float B_arr[] = {
                   a.x - ray.p0.x, a.x - c.x, ray.d.x,
                   a.y - ray.p0.y, a.y - c.y, ray.d.y,
                   a.z - ray.p0.z, a.z - c.z, ray.d.z,
                };

        float G_arr[] = {
                   a.x - b.x, a.x - ray.p0.x, ray.d.x,
                   a.y - b.y, a.y - ray.p0.y, ray.d.y,
                   a.z - b.z, a.z - ray.p0.z, ray.d.z,
                };

        float T_arr[] = {
                   a.x - b.x, a.x - c.x, a.x - ray.p0.x,
                   a.y - b.y, a.y - c.y, a.y - ray.p0.y,
                   a.z - b.z, a.z - c.z, a.z - ray.p0.z,
                };

        array2mat3(A, A_arr);
        array2mat3(B, B_arr);
        array2mat3(G, G_arr);
        array2mat3(T, T_arr);

        float A_det = glm::determinant(A);

        // TODO - is this float cmp correct?
        if (A_det == 0) {
            return 0;
        }

        float beta, gamma, t;

        t = glm::determinant(T) / A_det;
        if (t < 0) {
            return 0;
        }

        beta = glm::determinant(B) / A_det;
        if (beta < 0 || beta > 1) {
            return 0;
        }

        gamma = glm::determinant(G) / A_det;
        if (gamma < 0 || gamma > 1 - beta) {
            return 0;
        }

        return t;
    }

    vec3 getNormal(vec3 pos) {
        return glm::normalize(glm::cross(c2-c1, c3-c1));
    }

    vec3 c1;
    vec3 c2;
    vec3 c3;
};

#endif
