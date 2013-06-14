// from Texturing and Modeling: A procedural approach 3ed.

// for use with fBm functions


#include <math.h>
#include <stdlib.h>

#include "gnoise.h"

#define SMOOTHSTEP(x)  ((x)*(x)*(3 - 2*(x)))
// #define SMOOTHSTEP(x)  ((x)*(x)*(x) * ((x) * ((x) * 6.0f - 15.0f) + 10.0f))


#define RANDMASK 0xfffffff
#define RANDNBR ((random() & RANDMASK)/(double) RANDMASK)

#define TABSIZE 256
#define TABMASK  (TABSIZE-1)
#define PERM(x) perm[x % TABMASK]
#define INDEX(ix,iy,iz) PERM((ix)+PERM((iy)+PERM(iz)))

#define FLOOR(x) ((float) ((int) (x)))

static unsigned char perm[TABSIZE] = { 225, 155, 210, 108, 175, 199, 221, 144,
    203, 116, 5, 82, 173, 133, 222, 139, 174, 169, 138, 248, 36, 2, 151, 194,
    235, 65, 224, 217, 27, 81, 7, 22, 121, 229, 63, 8, 165, 110, 237, 117, 231,
    51, 172, 157, 47, 162, 115, 44, 43, 124, 94, 150, 53, 131, 84, 57, 220, 197,
    58, 24, 15, 179, 18, 215, 153, 26, 200, 226, 119, 12, 76, 34, 187, 140, 164,
    236, 232, 120, 70, 213, 69, 158, 33, 252, 90, 246, 75, 130, 91, 191, 25,
    113, 228, 159, 205, 253, 134, 142, 89, 103, 96, 104, 156, 80, 212, 176, 250,
    16, 141, 247, 50, 208, 39, 49, 32, 10, 198, 223, 255, 11, 241, 46, 31, 123,
    168, 125, 249, 17, 201, 129, 20, 181, 111, 239, 218, 87,  55, 73, 112, 182,
    244, 195, 227, 1, 243, 148, 102, 166, 28, 99, 242, 136, 189, 72, 3, 192, 62,
    202, 6, 128, 167, 23, 188, 13, 35, 77, 196, 185, 68, 183, 230, 177, 135,
    160, 180, 38, 238, 251, 37, 240, 126, 64, 74, 161, 40, 66, 29, 59, 146, 61,
    254, 107, 42, 86, 154, 4, 21, 233, 209, 45, 98, 193, 114,  184, 149, 171,
    178, 101, 48, 41, 71, 56, 132, 211, 152, 170, 163,  106, 9, 79, 147, 85, 30,
    207, 219, 137, 214, 145, 93, 92, 100, 245, 54, 78, 19, 206, 88, 234, 190,
    122, 0, 216, 186, 60, 95, 83, 105, 14, 118, 127, 67, 143, 109, 97, 204, 52 };



static float gradientTab[TABSIZE*3];

static void gradientTabInit(int seed);
static float glattice(int ix, int iy, int iz, float fx, float fy, float fz);

float gnoise(glm::vec3 v) {
    return gnoise(v.x, v.y, v.z);
}

float gnoise(float x, float y, float z)
{
    int ix, iy, iz;
    float fx0, fx1, fy0, fy1, fz0, fz1;
    float wx, wy, wz;
    float vx0, vx1, vy0, vy1, vz0, vz1;
    static int initialized = 0;

    if (!initialized) {
        gradientTabInit(665);
        initialized = 1;
    }

    ix = FLOOR(x);
    fx0 = x - ix;
    fx1 = fx0 - 1;
    wx = SMOOTHSTEP(fx0);

    iy = FLOOR(y);
    fy0 = y - iy;
    fy1 = fy0 - 1;
    wy = SMOOTHSTEP(fy0);

    iz = FLOOR(z);
    fz0 = z - iz;
    fz1 = fz0 - 1;
    wz = SMOOTHSTEP(fz0);

    vx0 = glattice(ix,iy,iz,fx0,fy0,fz0);
    vx1 = glattice(ix+1,iy,iz,fx1,fy0,fz0);
    vy0 = LERP(wx, vx0, vx1);
    vx0 = glattice(ix,iy+1,iz,fx0,fy1,fz0);
    vx1 = glattice(ix+1,iy+1,iz,fx1,fy1,fz0);
    vy1 = LERP(wx, vx0, vx1);
    vz0 = LERP(wy, vy0, vy1);

    vx0 = glattice(ix,iy,iz+1,fx0,fy0,fz1);
    vx1 = glattice(ix+1,iy,iz+1,fx1,fy0,fz1);
    vy0 = LERP(wx, vx0, vx1);
    vx0 = glattice(ix,iy+1,iz+1,fx0,fy1,fz1);
    vx1 = glattice(ix+1,iy+1,iz+1,fx1,fy1,fz1);
    vy1 = LERP(wx, vx0, vx1);
    vz1 = LERP(wy, vy0, vy1);

    return LERP(wz, vz0, vz1);
}


// returns notmal at point
void normal_gnoise(glm::vec3 &N, float x, float y, float z)
{
    int ix, iy, iz;
    float fx0, fx1, fy0, fy1, fz0, fz1;
    float wx, wy, wz;
    float vx0, vx1, vy0, vy1, vz0, vz1;
    static int initialized = 0;

    if (!initialized) {
        gradientTabInit(665);
        initialized = 1;
    }

    ix = FLOOR(x);
    fx0 = x - ix;
    fx1 = fx0 - 1;
    wx = SMOOTHSTEP(fx0);

    iy = FLOOR(y);
    fy0 = y - iy;
    fy1 = fy0 - 1;
    wy = SMOOTHSTEP(fy0);

    iz = FLOOR(z);
    fz0 = z - iz;
    fz1 = fz0 - 1;
    wz = SMOOTHSTEP(fz0);

    const float w = fx0;
    const float u = fy0;
    const float v = fz0;

    // for u'(x) for u(x) = 3 x^2 -2 x^3 (SMOOTHSTEP)
    const float dx = 6 * fx0 * (1 - fx0);
    const float dy = 6 * fy0 * (1 - fy0);
    const float dz = 6 * fz0 * (1 - fz0);

    // get parameters to calculate normal. from iquilzles.org about perlin noise
    float a,b,c,d,e,f,g,h;

    a = vx0 = glattice(ix,iy,iz,fx0,fy0,fz0);
    b = vx1 = glattice(ix+1,iy,iz,fx1,fy0,fz0);
    vy0 = LERP(wx, vx0, vx1);
    c = vx0 = glattice(ix,iy+1,iz,fx0,fy1,fz0);
    d = vx1 = glattice(ix+1,iy+1,iz,fx1,fy1,fz0);
    vy1 = LERP(wx, vx0, vx1);
    vz0 = LERP(wy, vy0, vy1);

    e = vx0 = glattice(ix,iy,iz+1,fx0,fy0,fz1);
    f = vx1 = glattice(ix+1,iy,iz+1,fx1,fy0,fz1);
    vy0 = LERP(wx, vx0, vx1);
    g = vx0 = glattice(ix,iy+1,iz+1,fx0,fy1,fz1);
    h = vx1 = glattice(ix+1,iy+1,iz+1,fx1,fy1,fz1);
    vy1 = LERP(wx, vx0, vx1);
    vz1 = LERP(wy, vy0, vy1);

    const float k0 =   a;
    const float k1 =   b - a;
    const float k2 =   c - a;
    const float k3 =   e - a;
    const float k4 =   a - b - c + d;
    const float k5 =   a - c - e + g;
    const float k6 =   a - b - e + f;
    const float k7 = - a + b + c - d + e - f - g + h;

    N.x = dx * (k1 + k4*v + k6*w + k7*v*w);
    N.y = dy * (k2 + k5*w + k4*u + k7*w*u);
    N.z = dz * (k3 + k6*u + k5*v + k7*u*v);

    return;
}


static void
gradientTabInit(int seed)
{
    float *table = gradientTab;
    float z, r, theta;
    int i;

    srandom(seed);
    for(i = 0; i < TABSIZE; i++) {
        z = 1. - 2.*RANDNBR;
        /* r is radius of x,y circle */
        r = sqrtf(1 - z*z);
        /* theta is angle in (x,y) */
        theta = 2 * M_PI * RANDNBR;
        *table++ = r * cosf(theta);
        *table++ = r * sinf(theta);
        *table++ = z;
    }
}

static float
glattice(int ix, int iy, int iz,
    float fx, float fy, float fz)
{
    float *g = &gradientTab[INDEX(ix,iy,iz)*3];
    return g[0]*fx + g[1]*fy + g[2]*fz;
}
