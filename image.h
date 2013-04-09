
#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// TODO put in class?

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



Image init_image(int w, int h);
void free_image(int w, int h, Image image);
void write_image(std::string fname);



#endif /* image_h */
