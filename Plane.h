#ifndef PLANE_H
#define PLANE_H

#include <string>
#include "glm/glm.hpp"
#include "util.h"

#include "BaseObject.h"
#include "GeomObj.h"

using std::string;



class Plane : public GeomObject {

public:

    Plane() {
        name = "plane";
    }

    void read(istream &in) {

        char dummy;
        string property("");

        skip_to(in, '{');
        // cout << "read '" << dummy << "'\n";

        read_vec3(in, location);

        skip_to(in, ',');

        in >> distance;

        GeomObject::read(in);
    }

    virtual float intersect(const Ray &ray) {
        /* http://www.siggraph.org/education/materials/HyperGraph/raytrace/rayplane_intersection.htm
           t = -(N . P0 -D)/ (N . d)
        */

        float nd = dot(location, ray.d);
        if (nd == 0) {
            // parallel
            return 0;
        }
        
        // location is the normal for the plane
        float npd = distance - dot(location, ray.p0);

        float t = npd / nd;

        return t;
    }

    vec3 getNormal(vec3 pos) {
        return location;
    }

    void print_properties() {
        cout << "distance: " << distance << endl;
        GeomObject::print_properties();
    }

    float distance;
};

#endif
