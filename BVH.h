#ifndef BVH_H
#define BVH_H


#include "GeomObj.h"
#include "BBox.h"

#include <vector>

#include <algorithm>


using std::vector;

bool cmpXaxis(GeomObject *a, GeomObject *b) {
    return a->box.center.x < b->box.center.x;
}
bool cmpYaxis(GeomObject *a, GeomObject *b) {
    return a->box.center.y < b->box.center.y;
}
bool cmpZaxis(GeomObject *a, GeomObject *b) {
    return a->box.center.z < b->box.center.z;
}

struct BVHNode : GeomObject {


    static const int X_AXIS = 0;
    static const int Y_AXIS = 1;
    static const int Z_AXIS = 3;


    BVHNode() {

    }


    BVHNode(vector<GeomObject *> &obj_vec, int start, int end, int axis) {
        int num_geom = end - start;

        if (num_geom == 1) {
            right = obj_vec[start];
            left = NULL;

            box = right->box;
        } else if (num_geom == 2) {
            right = obj_vec[start];
            left = obj_vec[start+1];

            box = right->box + left->box;
            
        } else if (num_geom == 0) {
            right = NULL;
            left = NULL;
        } else {
            // partition
            int mid = partition_objs(obj_vec, start, end, axis);

            // recursive call
            left = new BVHNode(obj_vec, start, mid, (axis + 1) % 3);
            right = new BVHNode(obj_vec, mid, end, (axis + 1) % 3);

            box = right->box + left->box;
        }
    }


    int partition_objs(vector<GeomObject *> &obj_vec, int start, int end, int axis) {

        typedef bool(*cmpFunc)(GeomObject *a, GeomObject *b);
        cmpFunc cmpFuncs[3] = {cmpXaxis, cmpYaxis, cmpZaxis};


        std::sort(obj_vec.begin() + start, obj_vec.end() + end, cmpFuncs[axis]);

        int mid = (start + end) / 2;

        return mid;
    }


    GeomObject *left;
    GeomObject *right;

    BBox box;
};


#endif /* BVH_H */
