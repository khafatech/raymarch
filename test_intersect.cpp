#include <iostream>
using namespace std;

#include "Sphere.h"

#include "BBox.h"
#include "Box.h"



void test_intersect(GeomObject &obj, Ray &ray) {
}


void print_hit(Hit *hit) {
    if (hit) {
        cout << "t: " << hit->t << endl;
    } else {
        printf("no hit\n");
    }
}


int main(void) {

    
    float t;

    /*
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

    Hit *hit;

    hit = sphere1.intersect(r1);
    cout << "r1->s1: ";
    print_hit(hit);

    hit = sphere2.intersect(r2);
    cout << "r2->s2: ";
    print_hit(hit);
    */

    
    Ray r3;
    r3.p0 = vec3(5, 0.5, 0);
    r3.d = vec3(-1, 0, 0);
    
    BBox box1(vec3(0,0,0), vec3(1,1,1));

    BBox box2(vec3(-1,0.5,0.5), vec3(1,1,3));
    BBox box3 = box1 + box2;


    Box geomBox1(box1);
    vec3 norm1 = geomBox1.getNormal(vec3(-3.1, -10, 0.5));
    print3f(norm1, "norm1");

    Hit *hit;
    hit = geomBox1.intersect(r3);
    cout << "gbox1 :";
    print_hit(hit);


    
    t = box1.intersect(r3);
    cout << "box3 x r3: " << t << endl;
    cout << "box3:\n";
    box3.print_properties();


    return 0;
}



