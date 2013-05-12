
#ifndef GEOM_OBJECT_H
#define GEOM_OBJECT_H

#include <iostream>
#include <string>

#include "glm/gtc/matrix_transform.hpp"
#include "util.h"
#include "Ray.h"

using std::string;
using std::istream;
using glm::vec3;
using glm::vec4;
using glm::mat4;

using namespace std;


struct Pigment {

    Pigment() {
        color = vec4(0.0, 0.0, 0.0, 0.0);
    }

    void read(istream &in) {

        string dummy;
        skip_to(in, '{');

        in >> dummy;
        in >> dummy;

        if (dummy.size() == 4) {
            // rgbf
            read_vec4(in, color);
        } else {
            // rgb
            vec3 color3;
            read_vec3(in, color3);

            color.x = color3.x;
            color.y = color3.y;
            color.z = color3.z;
            color.w = 0.0;
        }
        skip_to(in, '}');
    }

    vec3 to_vec3() {
        return vec3(color.x, color.y, color.z);
    }

    vec4 color;
};



struct Finish {
    Finish() {
        ambient = diffuse = specular = roughness = reflection = refraction = ior = 0;
    }

    void read(istream &in) {
        skip_to(in, '{');

        string property;

        while (property != "}" && !in.eof()) {
            in >> property;

            if (property == "ambient") {
                in >> ambient;
            } else if (property == "diffuse") {
                in >> diffuse;
            } else if (property == "specular") {
                in >> specular;
            } else if (property == "roughness") {
                in >> roughness;
            } else if (property == "reflection") {
                in >> reflection;
            } else if (property == "refraction") {
                in >> refraction;
            } else if (property == "ior") {
                in >> ior;
            }
        }
    }

    void print_properties() {
        cout << "finish:" << endl;
        cout << "ambient " << ambient << endl;
        cout << "diffuse " << diffuse<< endl;
        cout << "specular " << specular<< endl;
        cout << "roughness " << roughness<< endl;
        cout << "reflection " << reflection<< endl;
        cout << "refraction " << refraction<< endl;
        cout << "ior " << ior << endl;
    }

    float ambient, diffuse, specular, roughness, reflection, refraction, ior;
};



class GeomObject : public BaseObject {

public:
    
    virtual void read(istream &in) {
        string property;

        mat4 xmat = mat4(1.0);

        while (property != "}" && !in.eof()) {
            in >> property;

            if (property == "pigment") {
                pigment.read(in);
            } else if (property == "finish") {
                finish.read(in);
            } else if (property == "translate") {
                read_vec3(in, translate);
                xmat = glm::translate(mat4(1.0), translate) * xmat;
            }  else if (property == "rotate") {
                read_vec3(in, rotate);
                xmat = glm::rotate(mat4(1.0), rotate.x, vec3(1,0,0)) * xmat;
                xmat = glm::rotate(mat4(1.0), rotate.y, vec3(0,1,0)) * xmat;
                xmat = glm::rotate(mat4(1.0), rotate.z, vec3(0,0,1)) * xmat;
            } else if (property == "scale") {
                read_vec3(in, scale);
                xmat =  glm::scale(mat4(1.0), scale) * xmat;
            }
        }

        xmat_i = glm::inverse(xmat);
        xmatT = glm::transpose(xmat_i);
    }
    
    virtual void print_properties() {
        print3f(translate, "translate");
        print3f(rotate, "rotate");
        print3f(scale, "scale");
        print4f(pigment.color, "pigment color");
        finish.print_properties();
    }

    virtual float intersect(const Ray &ray) {
        // cerr << "hurrr\n";
        return 0;
    }

    virtual vec3 getNormal(vec3 pos) {
        // cout << "hurrr " << name << endl;
        return vec3(0.0);
    }


protected:
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

public:
    
    Pigment pigment;
    Finish finish;

    vec3 translate;
    vec3 rotate;
    vec3 scale;

    mat4 xmat_i;
    mat4 xmatT;
};

#endif
