
#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "GeomObj.h"

using namespace std;

struct Color {

    Color(int r0, int g0, int b0) {
        r = r0;
        g = g0;
        b = b0;
    }
    
    Color() {
        r = g = b = 0;
    }

    Color& operator=(const vec3 &rhs) {
        r = MIN(255 * rhs.x, 255);
        g = MIN(255 * rhs.y, 255);
        b = MIN(255 * rhs.z, 255);

        return *this;
    }

    Color& operator=(const Pigment &rhs) {
        r = 255 * rhs.color.x;
        g = 255 * rhs.color.y;
        b = 255 * rhs.color.z;

        return *this;
    }
    
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

typedef Color** Image;



Image init_image(int w, int h);
void free_image(int w, int h, Image image);
void write_image(Image, std::string fname);



#endif /* image_h */
