


#include <iostream>
using namespace std;

#include "Sphere.h"




void test_intersect(GeomObject &obj, Ray &ray) {
}


int main(void) {

    


    Ray r1;
    r1.p0 = vec3(1, 2, 0);
    r1.d = vec3(1, 0, 0);
    Sphere sphere1;
    sphere1.location = vec3(5, 2, 0);
    sphere1.radius = 1;

    Ray r2;
    r2.p0 = vec3(1, 0.9, 13);
    r2.d = vec3(0, 0, -1);

    Sphere sphere2;
    sphere2.location = vec3(0, 0, 0);
    sphere2.radius = 2;


    
    float t;
    t = sphere1.intersect(r1);
    cout << "r1->s1: " << t << endl;

    t = sphere2.intersect(r2);
    cout << "r2->s2: " << t << endl;


    return 0;
}



