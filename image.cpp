
#include "image.h"

using namespace std;

extern int g_image_width;
extern int g_image_height;

extern Image g_image;


// image: [col1, col2, ... ] 

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

    for (int y=0; y < h; y++)
    for (int x=0; x < w;x++) {
        image[x][y] = Color(0, 0, 0);
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
