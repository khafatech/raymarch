
from math import sin, cos, pi


def print3f(vec):
    print "<", ",".join("%f" % n for n in vec), ">"

def print4f(vec, w):
    print "<", ",".join("%f" % n for n in vec), ", ", w, " >"

def print_sphere(pos, r, color=[1,0,0]):
    print "sphere {"
    print3f(pos)
    print ", ", r

    print """ pigment { color rgba """
    print4f(color, 1)

    print """ }
        finish {ambient 0.2 diffuse 0.2 reflection 0.0 refraction 0.9 ior 1.33}
        translate <0, 0, 0>
        }
    """

def print_sphere_reg(pos, r, color=[1,0,0]):
    print "sphere {"
    print3f(pos)
    print ", ", r

    print """ pigment { color rgb """
    print3f(color)

    print """ }
        finish {ambient 0.2 diffuse 1 reflection 0.5}
        translate <0, 0, 0>
        }
    """

def print_hdr():
    print """
        camera {
          location  <0, 20, 30>
          up        <0,  1,  0>
          right     <1.33333, 0,  0>
          look_at   <0, 0, 0>
        }

        light_source {<-100, 100, 10> color rgb <1.5, 1.5, 1.5>}
        light_source {<10, -50, 30> color rgb <1.5, 1, 1>}
        """



def color_map(x):
    return [0.5 * (sin(2*pi*x) + 1), 0.5 * (cos(2*pi*x) + 1), 0.5]
    

print_hdr()

from random import random

for i in range(-15, 15, 5):
    for j in range(-15, 15, 5):
        print_sphere([i, j + 0.5 * (random()) ,0], 1 + 3 * random(), color_map((i)/20.0))

for i in range(-20, 20, 4):
    for j in range(-20, 20, 4):
        print_sphere_reg([i, j -10, -20], 3, color_map((i)/20.0))


