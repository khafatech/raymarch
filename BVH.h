#ifndef BVH_H
#define BVH_H

#include "BBox.h"



struct BVHNode : GeomObject {


    static const int X_AXIS = 0;
    static const int Y_AXIS = 1;
    static const int Z_AXIS = 3;


    BVHNode() {

    }


    BVHNode(vector<GeomObject *> obj_vec, int start, int end, int axis) {
        int num_geom = end - start;

        if (num_geom == 1) {
            right = obj_vec[start];
            left = NULL;

            box = right->box;
        } else if (num_geom == 2) {
            right = obj_vec[start];
            left = obj_vec[start+1];

            box = right->box + left->box; // TODO
        } else {

            // comment

        }
    }


    GeomObject *left;
    GeomObject *right;

    BBox box;
};


#endif /* BVH_H */
