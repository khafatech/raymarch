#ifndef BVH_H
#define BVH_H


#include "GeomObj.h"
#include "BBox.h"
#include "Sphere.h"
#include "Ray.h"



#include <vector>

#include <algorithm>

#include <iostream>
using namespace std;




using std::vector;

bool cmpXaxis(GeomObject *a, GeomObject *b) {
    // cout << "cmpX: geomObj a:" << a << ", b: " << b << endl;
    return a->box.center.x < b->box.center.x;
}
bool cmpYaxis(GeomObject *a, GeomObject *b) {
    // cout << "cmpY: geomObj a:" << a << ", b: " << b << endl;
    return a->box.center.y < b->box.center.y;
}
bool cmpZaxis(GeomObject *a, GeomObject *b) {
    // cout << "cmpZ: geomObj a:" << a << ", b: " << b << endl;
    return a->box.center.z < b->box.center.z;
}

struct BVHNode : GeomObject {


    static const int X_AXIS = 0;
    static const int Y_AXIS = 1;
    static const int Z_AXIS = 3;


    BVHNode() {

    }



    void print_tabs(int depth) {
        while (depth--) {
            cout << "  ";
        }
    }

    void print() {
        print(this, 0);
    }

    void print(GeomObject *node, int depth) {
        
        Sphere *sphere;

        BVHNode *bvhNode;

        if (node == NULL) {
            print_tabs(depth);
            cout << "NULL\n";
            return;
        } else if ((sphere = dynamic_cast<Sphere *>(node))) {
            print_tabs(depth);
            cout << "sphere. r: " << sphere->radius << ", ";
            print3f(sphere->location, "pos");
        } else if ((bvhNode = dynamic_cast<BVHNode *>(node))) {

            // === print box ===
            print_tabs(depth);
            cout << "*box:\n";
            
            print_tabs(depth+2);
            print3f(bvhNode->box.min, "min");

            print_tabs(depth+2);
            print3f(bvhNode->box.max, "max");
            // === end print box ===

            print_tabs(depth);
            cout << "*left: " <<endl;
            print(bvhNode->left, depth+1);

            print_tabs(depth);
            cout << "*right: " <<endl;
            print(bvhNode->right, depth+1);
        }

    }


    Hit* intersect(const Ray &ray) {
        return intersect(this, ray);
    }

    Hit* intersect(GeomObject* node, const Ray &ray) {
        Hit* leftHit = NULL;
        Hit* rightHit = NULL;

        Hit* retHit = NULL;

        if (node == NULL) {
            return NULL;
        }

        if (node->box.intersect(ray) <= 0) {
            return NULL;
        }

        BVHNode *bvhNode;

        if ((bvhNode = dynamic_cast<BVHNode *>(node))) {

            if (bvhNode->left != NULL) {
                leftHit = bvhNode->left->intersect(ray);
            }
            if (bvhNode->right != NULL) {
                rightHit = bvhNode->right->intersect(ray);
            }

            if (leftHit && rightHit) {
                // ret smallest
                
                if (leftHit->t < rightHit->t) {
                    retHit = leftHit;
                } else {
                    retHit = rightHit;
                }

            } else if (leftHit) {
                retHit = leftHit;
            } else if (rightHit) {
                retHit = rightHit;
            } else {
                retHit = NULL;
            }
        } else {
            retHit = node->intersect(ray);
        }

        // clean up
        if (leftHit && (leftHit != retHit)) {
            delete leftHit;
        }
        if (rightHit && (rightHit != retHit)) {
            delete rightHit;
        }

        return retHit;
    }

    BVHNode(vector<GeomObject *> &obj_vec) {
        newBVHNode(obj_vec, 0, (int) obj_vec.size(), 0);
    }

    BVHNode(vector<GeomObject *> &obj_vec, int start, int end, int axis) {
        newBVHNode(obj_vec, start, end, axis);
    }

protected:
    void newBVHNode(vector<GeomObject *> &obj_vec, int start, int end, int axis) {
        int num_geom = end - start;

        // cout << "\n** BVHNode: start: " << start << " end: " << end << endl;

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


        std::sort(obj_vec.begin() + start, obj_vec.begin() + end, cmpFuncs[axis]);

        int mid = (start + end) / 2;

        return mid;
    }

    GeomObject *left;
    GeomObject *right;
};


#endif /* BVH_H */
