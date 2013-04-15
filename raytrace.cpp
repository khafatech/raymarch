/* raytrace.cpp
 * Ray tracer
 *
 * Mustafa Khafateh
 * CSC 473 Spring 2013
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <vector>


using namespace std;

#include "image.h"

#include "Camera.h"
#include "LightSource.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Triangle.h"
#include "Ray.h"


// default values
int g_image_width = 640;
int g_image_height = 480;

Image g_image;



vector<BaseObject*> theObjects;
vector<BaseObject*> g_lights;
vector<GeomObject*> g_geom;

Camera *g_camera;


void draw_circle(int r) {
    
    for (int y=0; y < g_image_height; y++) {
    	for (int x=0; x < g_image_width; x++) {
    	    
    	    if ((POWER2(x-g_image_width/2) + POWER2(y-g_image_height/2)) < 
    	         POWER2(r)) {
    	        g_image[x][y] = Color(0, ((y + 10) * 40) % 255, (y * 40) % 255);
    	    }
    	}
    }
}




void parse_pov(const string fname) {

    ifstream in;
    in.open(fname.c_str(), ifstream::in);

    string word;
    BaseObject *read_obj;

    while (!in.eof()) {
        in >> word;

        if (in.eof()) {
            break;
        }
        cout << "read '" << word << "'  eof: " << in.eof() << endl;

        if (word.size() > 0 && word[0] == '/') {
            // comment
            dprint("read comment");
            skip_line(in);
            continue;
        }

        read_obj = NULL;

        if (word == "camera") {
            dprint("read camera");
            g_camera = new Camera();
            read_obj = g_camera;
        } else if (word == "light_source") {
            read_obj = new LightSource();
            g_lights.push_back(read_obj);
        } else if (word == "box") {
            read_obj = new Box();
        } else if (word == "plane") {
            read_obj = new Plane();
        } else if (word == "triangle") {
            read_obj = new Triangle();
        } else if (word == "sphere") {
            read_obj = new Sphere();
        } else if (word == "cone") {
        }

        if (read_obj != NULL) {
            read_obj->read(in);
            theObjects.push_back(read_obj);

            if (dynamic_cast<GeomObject *>(read_obj)) {
                g_geom.push_back((GeomObject *) read_obj);
            }
        }
    }

    in.close();

}


// represents an intersection
struct Hit {
    Hit(float t, GeomObject *obj) {
        this->t = t;
        this->obj = obj;
    }
    float t;
    GeomObject *obj;
};



Hit* find_closest_hit(vector<Hit*> &hits) {
    if (hits.empty()) {
        return NULL;
    }

    int smallestIndex = 0;
    
    for (int i=0; i < hits.size(); i++) {
        if (hits[i]->t < hits[smallestIndex]->t) {
            smallestIndex = i;
        }
    }
    return hits[smallestIndex];
}


void cast_rays() {
    Ray *ray;
    GeomObject *cur_obj = dynamic_cast<GeomObject *>(theObjects[2]);
    cout << "casting: " << cur_obj->name << endl;
    cur_obj->print_properties();

    // TODO parametrize max distance (doesn't work now)
    Hit closest_hit(1000, NULL);

    float t;
    for (int y=0; y < g_image_height; y++)
    for (int x=0; x < g_image_width; x++) {
        // ray = g_camera->genOrthoRay(x, y);
        ray = g_camera->genRay(x, y);

        // intersect ray with geometry
        for (int i=0; i < g_geom.size(); i++) {
            t = g_geom[i]->intersect(*ray);
            if (t > 0 && (closest_hit.obj == NULL || t < closest_hit.t)) {
                closest_hit.t = t;
                closest_hit.obj = g_geom[i];
            }
        }

        // t = cur_obj->intersect(*ray);
        // cout << "t: " << t << endl;

        if (closest_hit.obj) {
            g_image[x][y] = closest_hit.obj->pigment;
        }

        closest_hit.obj = NULL;

        delete ray;
    }
}

int main(int argc, char* argv[]) {

    if (argc != 4) {
        cerr << "usage: " << argv[0] << " width height -Iinput.pov\n";
        exit(1);
    }

    g_image_width = atoi(argv[1]); 
    g_image_height = atoi(argv[2]); 

    if (g_image_width <= 0 || g_image_height <= 0) {
        cerr << "Error: Width and height must be positive\n";
        exit(1);
    }

    string fname(argv[3] + 2);
    parse_pov(fname);

    // print objects
    /*
    for (int i=0; i<theObjects.size(); i++) {
        cout << endl << endl << theObjects[i]->name << ":\n";
        theObjects[i]->print_properties();
    }
    */

    cout << "w: " << g_image_width << " h: " << g_image_height
         << " fname: " << fname << endl;

    g_image = init_image(g_image_width, g_image_height);

    g_camera->setImageDimention(g_image_width, g_image_height);


    // the main thing
    cast_rays();

    // test
    // draw_circle(g_image_height/3);

    // works only with ppm now
    string outfile_name(fname + ".ppm");
	write_image(outfile_name);
	

    return 0;
}
