#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include "glm/glm.hpp"
#include <iostream>

using std::istream;
using glm::vec3;
using glm::vec4;

void read_vec3(istream &in, vec3 &v);
void read_vec4(istream &in, vec4 &v);
void skip_to(istream &in, char target_ch);
void skip_line(istream &in);

float max(float a, float b);
float min(float a, float b);

#define print3f(v, name) \
        printf("%s: %f %f %f\n", name, v.x, v.y, v.z);

#define print4f(v, name) \
        printf("%s: %f %f %f %f\n", name, v.x, v.y, v.z, v.w);

#define vec4_to_vec3(v4) vec3(v4.x, v4.y, v4.z)

#define POWER2(x) ((x) * (x))

#define MAX(x, y) ((x) > (y)) ? (x) : (y);
#define MIN(x, y) ((x) < (y)) ? (x) : (y);


// #define RAYTRACE_DEBUG

#ifdef RAYTRACE_DEBUG
#define dprint(x) puts(x)
#else
#define dprint(x) ;
#endif


#endif
