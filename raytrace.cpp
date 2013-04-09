/* raytrace.cpp
 * Ray tracer
 *
 * Mustafa Khafateh
 * CSC 473 Spring 2013
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


using namespace std;

#include "image.h"

// default values
int g_image_width = 640;
int g_image_height = 480;

Image g_image;



#define POWER2(x) ((x) * (x))


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

    cout << "w: " << g_image_width << " h: " << g_image_height
         << " fname: " << fname << endl;

    g_image = init_image(g_image_width, g_image_height);

    // test
    draw_circle(g_image_height/3);
    
	write_image("out.ppm");
	

    return 0;
}
