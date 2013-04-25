


#include <stdio.h>

#include "util.h"


float max(float a, float b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

float min(float a, float b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void read_vec4(istream &in, vec4 &v) {
    char dummy;
    in >> dummy;
    in >> v.x;
    in >> dummy;
    in >> v.y;
    in >> dummy;
    in >> v.z;
    in >> dummy;
    in >> v.w;
    in >> dummy;
}

void read_vec3(istream &in, vec3 &v) {
    char dummy;
    in >> dummy;
    in >> v.x;
    in >> dummy;
    in >> v.y;
    in >> dummy;
    in >> v.z;
    in >> dummy;
}

void skip_to(istream &in, char target_ch) {
    char ch;
    do {
        in.get(ch);
    } while (!in.eof() && ch != target_ch);
}

void skip_line(istream &in) {
    skip_to(in, '\n');
    dprint("skipped comment");
}
