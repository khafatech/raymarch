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
#include <stdint.h>

using namespace std;


// default values
int g_image_width = 640;
int g_image_height = 480;


struct Color {

    Color(int r0, int g0, int b0) {
        r = r0;
        g = g0;
        b = b0;
    }
    
    Color() {
        r = g = b = 0;
    }
    
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

typedef Color** Image;
Image g_image;



// image: [col1, col2, ... ] 
// TODO put in class?

Image init_image(int w, int h) {
	
	Image image;

    image = (Color **) malloc(sizeof(Color *) * w);

    if (image == NULL) {
        perror("init_image: malloc.");
        exit(1);
    }

    for (int x=0; x < w; x++) {
        image[x] = (Color *) malloc(sizeof(Color) * h);

        if (image[x] == NULL) {
            perror("init_image: malloc.");
            exit(1);
        }
    }
    
    return image;
}

void free_image(int w, int h, Image image) {
    for (int x=0; x < w; x++) {
        free(image[x]);
    }
    
    free(image);
}



void write_image(string fname) {
    // ppm
    
    FILE *file = fopen(fname.c_str(), "w+");
    
    if (file == NULL) {
    	perror("error creating output image");
        exit(1);
    }
    
    fprintf(file, "P3\n%d %d\n255\n", g_image_width, g_image_height);
    
    for (int y=0; y < g_image_height; y++) {
    	for (int x=0; x < g_image_width; x++) {
	   	    fprintf(file, "%d %d %d\n",
	   	     g_image[x][y].r, g_image[x][y].g, g_image[x][y].b);
    	}
    }
    
    fclose(file);
}

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
