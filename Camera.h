#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "glm/glm.hpp"

#include "util.h"
#include "BaseObject.h"
#include "Ray.h"

using glm::vec3;
using glm::normalize;
using glm::length;
using std::string;





class Camera : public BaseObject {

public:

    Camera() {
        name = "camera";
    }


    // x and y are image coordinates
    void setImageDimention(int x, int y) {
        image_w = x;
        image_h = y;
    }

    /*
       equations from Shirley section 10.2

       in the image's coords:
       u_s = l + (r - l) * (i + 0.5)/n_x
       v_s = l + (r - l) * (i + 0.5)/n_x

    

    */

    // input: image x and y
    // returns ray in world coords
    Ray* genRay(float x, float y) {
        Ray *ray = new Ray();


        // uses aspect ratio form pov
        float r = length(right) / 2.0;
        float top = length(up) / 2.0;


        // TODO - randomize x,y +- 0.5


        vec3 u;
        vec3 w = normalize(look_at - location);
        
        // pixel to cam coords
        u.x = -r + 2 * r * (x + 0.5) / image_w;
        u.y = top - 2 * top * (y + 0.5) / image_h;
        u.z = 1; // 1 far from camera
        
        // cam to world coords
        ray->p0 = location + vec3(u.x) * normalize(right)
                  + vec3(u.y) * up
                  + vec3(u.z) * w;

        ray->d = ray->p0 - location;

        return ray;

    }

    Ray* genOrthoRay(int x, int y) {
        Ray *ray = new Ray();

        // only for ortho
        ray->d = normalize(look_at - location);

        // TODO - put aspect ratio
        float r = 5 * 1.33333;
        float top = 5 * 1;

        vec3 u;
        
        // pixel to cam coords
        u.x = -r + 2 * r * (x + 0.5) / image_w;
        u.y = -top + 2 * top * (y + 0.5) / image_h;
        u.z = 1; // 1 far from camera
        
        // cam to world coords
        ray->p0 = location + vec3(u.x) * normalize(right)
                  + vec3(u.y) * up
                  + vec3(u.z) * ray->d;

        return ray;
    }

    // parse pov
    void read(istream &in) {

        string property;

        skip_to(in, '{');
        // cout << "read '" << dummy << "'\n";

        while (property != "}") {
            in >> property;

            // cout << "read '" << property << "'\n";

            if (property == "location") {
                read_vec3(in, location);
            } else if (property == "up") {
                read_vec3(in, up);
            } else if (property == "right") {
                read_vec3(in, right);
            } else if (property == "look_at") {
                read_vec3(in, look_at);
            }
        }
    }

    void print_properties() {
        print3f(location, "loc");
        print3f(up, "up");
        print3f(right, "right");
        print3f(up, "look_at");
    }

    vec3 up;
    vec3 right;
    vec3 look_at;

    int image_w;
    int image_h;
};

#endif
