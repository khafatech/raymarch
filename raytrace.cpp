/* raytrace.cpp
 * Ray tracer!
 *
 * Mustafa Khafateh
 * CSC 473 Spring 2013
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


using namespace std;


// default values
int g_image_width = 640;
int g_image_height = 480;


struct Color {
    char r;
    char g;
    char b;
};

Color **g_image;



// image: [col1, col2, ... ] 
// TODO put in class?

void init_image(int w, int h, Color **image) {

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
}

void free_image(int w, int h, Color **image) {

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

    init_image(g_image_width, g_image_height, g_image);




    return 0;
}
