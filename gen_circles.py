
from math import sin, cos, pi


def print3f(vec):
    print "<", ",".join("%f" % n for n in vec), ">"

def print_sphere(pos, r, color=[1,0,0]):
    print "sphere {"
    print3f(pos)
    print ", ", r

    print """ pigment { color rgb """
    print3f(color)

    print """ }
        finish {ambient 0.2 diffuse 0.4 reflection 0.5}
        translate <0, 0, 0>
        }
    """

def print_hdr():
    print """
        camera {
          location  <0, 0, 14>
          up        <0,  1,  0>
          right     <1.33333, 0,  0>
          look_at   <0, 0, 0>
        }

        light_source {<-10, 10, 0> color rgb <1.5, 1.5, 1.5>}
        """



def color_map(x):
    return [0.5 * (sin(2*pi*x) + 1), 0.5 * (cos(2*pi*x) + 1), 0.5]
    

print_hdr()


for i in range(-4, 4):
    r = i * i * 0.2
    r0 = (i-1) * (i-1) * 2
    x = i-r0
    print_sphere([2*i, 0, 0], r, color_map(i/10.0))



