/* terrain.cpp
 * Ray tracer
 * 
 * testing raymarching of perlin noise
 *
 *
 * Mustafa Khafateh
 * CSC 473 Spring 2013
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmath>

#include <vector>


using namespace std;

#include "image.h"
#include "util.h"

#include "Camera.h"
#include "LightSource.h"

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Triangle.h"
#include "Ray.h"
#include "BVH.h"

// default values
int g_image_width = 640;
int g_image_height = 480;

Image g_image;



vector<BaseObject*> theObjects;
vector<LightSource*> g_lights;
vector<GeomObject*> g_geom;

BVHNode *g_obj_tree;


Camera *g_camera;


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




void parse_pov(const string fname) {

    ifstream in;
    in.open(fname.c_str(), ifstream::in);

    if (!in.is_open()) {
        cerr << "can't open file: " << fname << endl;
        exit(1);
    }

    string word;
    BaseObject *read_obj;

    while (!in.eof()) {
        in >> word;

        if (in.eof()) {
            break;
        }
        // cout << "read '" << word << "'  eof: " << in.eof() << endl;

        if (word.size() > 0 && word[0] == '/') {
            // comment
            dprint("read comment");
            skip_line(in);
            continue;
        }

        read_obj = NULL;

        if (word == "camera") {
            dprint("read camera");
            g_camera = new Camera();
            read_obj = g_camera;
        } else if (word == "light_source") {
            read_obj = new LightSource();
            g_lights.push_back((LightSource*) read_obj);
        } else if (word == "box") {
            read_obj = new Box();
        } else if (word == "plane") {
            read_obj = new Plane();
        } else if (word == "triangle") {
            read_obj = new Triangle();
        } else if (word == "sphere") {
            read_obj = new Sphere();
        } else if (word == "cone") {
        }

        if (read_obj != NULL) {
            read_obj->read(in);
            theObjects.push_back(read_obj);

            if (dynamic_cast<GeomObject *>(read_obj)) {
                g_geom.push_back((GeomObject *) read_obj);
            }
        }
    }

    in.close();

}





Hit* find_closest_hit(const Ray &ray) {

    Hit * non_plane_hit = g_obj_tree->intersect(ray);

    // TODO - test for planes

    return non_plane_hit;
}


bool blocked_light(vec3 pos, LightSource *light) {

	Ray ray;
	
	ray.d = light->location - pos;
	ray.p0 = pos;
    

    // BVH
    Hit* hit = find_closest_hit(ray);
    if (hit) {
        if (hit->t > 0.00001 && hit->t < 1.0) {
            return true;
        }
    }
	
    /*
    // non bvh
    float t;
	for (unsigned int i=0; i < g_geom.size(); i++) {
        t = g_geom[i]->intersect(ray);
        // if between light and intersect pt.
        if (t > 1.00001 && t < 1.0) {
            return true;
        }
	} */


	return false;
}


vec3 (*calcLighting)(GeomObject *obj, vec3 N, vec3 pos, LightSource *light);


vec3 calcLightingGaussian(GeomObject *obj, vec3 N, vec3 pos, LightSource *light) {


    float NL;
    vec3 L;
    vec3 color;
    float specular;
    
    vec3 pigment3 = vec3(obj->pigment.color.x,
            obj->pigment.color.y, obj->pigment.color.z);

    L = glm::normalize(light->location - pos);
    NL = MAX(dot(N, L), 0);

    vec3 V = glm::normalize(g_camera->location - pos);

    float smoothness = obj->finish.roughness == 0 ? 1 : 1/obj->finish.roughness;

    // specular
    if (NL > 0) {
        specular = exp(-pow(dot(V, vec3(2.0) * NL * N - L), 2) /
                smoothness);
    } else {
        specular = 0;
    }
	
	if (obj->name == "sphere") {
		// cout << "NL: " << NL << endl;
	}

    color = light->color *
            (vec3(specular) * vec3(obj->finish.specular) +
            vec3(NL) * pigment3);

    return color;
}



vec3 calcLightingPhong(GeomObject *obj, vec3 N, vec3 pos, LightSource *light) {


    float NL;
    vec3 L;
    vec3 color;
    float specular;
    
    vec3 pigment3 = vec3(obj->pigment.color.x,
            obj->pigment.color.y, obj->pigment.color.z);
    

    L = glm::normalize(light->location - pos);
    NL = MAX(dot(N, L), 0);

    vec3 V = glm::normalize(g_camera->location - pos);

    float smoothness = obj->finish.roughness == 0 ? 1 : 1/obj->finish.roughness;

    // specular
    if (NL > 0) {
        specular = pow(Max(dot(V, vec3(2.0) * NL * N - L), 0), smoothness);
    } else {
        specular = 0;
    }

    /*
    Plane *plane;
    if ((plane = dynamic_cast<Plane *>(obj))) {
        pigment3 = plane->getColor(pos);
    }
    */
	
    color = light->color * (vec3(specular) * vec3(obj->finish.specular)
            + vec3(NL) * pigment3 * obj->finish.diffuse);

    return color;
}

vec3 calcLighting_all(GeomObject *obj, vec3 N, vec3 pos) {

    vec3 color = vec3(0.0f);

    vec3 pigment3 = vec3(obj->pigment.color.x,
            obj->pigment.color.y, obj->pigment.color.z);

    color = obj->finish.ambient * pigment3;

    for (int i=0; i < (int) g_lights.size(); i++) {
        // FIXME - enable shadows and fix
        //if (!blocked_light(pos, g_lights[i])) {
            color += calcLighting(obj, N, pos, g_lights[i]);
        //}
    }
    
    return color;
}



void add_epsilon(Ray &ray) {
    ray.p0 = ray.p0 + ray.d * vec3(0.0001);
}

void reflect_ray(Ray &ray, vec3 N, vec3 pos) {
    ray.p0 = pos;
    ray.d =  ray.d - vec3(2.0) * dot(N, ray.d) * N;
}

// psuedo code from Shirley's book, p. 214
bool refract_ray(const Ray &ray, const vec3 &pos, const vec3 N, Ray &t, float n_over_n1) {

    vec3 norm_d = normalize(ray.d);
    vec3 norm_n = normalize(N);

    float under_sqrt = 1 - POWER2(n_over_n1) * (1 - POWER2(dot(norm_d, norm_n)));

    vec3 first_term;

    if (under_sqrt < 0) {
        // total internal reflect
        return false;
    }

    first_term = n_over_n1 * (norm_d - norm_n * (dot(norm_d,norm_n)));

    t.d = first_term - norm_n * sqrt(under_sqrt);
    t.p0 = pos;

    add_epsilon(t);

    return true;
}


vec3 cast_ray(Ray &ray, int recursion_depth=6) {
    Hit closest_hit(-1, NULL);

    Hit *hit;

    // for lighting
    vec3 N;
    vec3 pos;
    
    Ray reflected_ray;

    vec3 final_color(0.0);


    // intersect ray with geometry

    hit = find_closest_hit(ray);

    if (hit) {
        // cout << "hit\n";
        closest_hit.t = hit->t;
        closest_hit.obj = hit->obj;
        delete hit;
    } else {
        return final_color;
    }

    /*
    // non bvh
    for (unsigned int i=0; i < g_geom.size(); i++) {
        t = g_geom[i]->intersect(ray);
        if (t > 0 && (closest_hit.obj == NULL || t < closest_hit.t)) {
            closest_hit.t = t;
            closest_hit.obj = g_geom[i];
        }
    }
    */


    Ray T;

    // ray trace!
    pos = ray.d * vec3(closest_hit.t) + ray.p0;
    N = closest_hit.obj->getNormal(pos);

    if (recursion_depth <= 1 ) {
        final_color = calcLighting_all(closest_hit.obj, N, pos);
    } else {

        // refract
        if (closest_hit.obj->finish.refraction > 0) {
            float d_dot_n = dot(ray.d, N);
            if (d_dot_n < 0) {
                // out of obj
                refract_ray(ray, pos, N, T, 1/closest_hit.obj->finish.ior);
                final_color = cast_ray(T, recursion_depth-1) *
                    (closest_hit.obj->finish.refraction);
            } else {
                // in obj0
                if (refract_ray(ray, pos, -N, T, closest_hit.obj->finish.ior/1)) {
                    // not total internal reflect
                    return cast_ray(T, recursion_depth-1) *
                           (closest_hit.obj->finish.refraction);
                } else {
                    return vec3(0);
                }
            }
        }

        // reflection
        if (closest_hit.obj->finish.reflection > 0) {
            reflect_ray(ray, N, pos);
            add_epsilon(ray);
            final_color += closest_hit.obj->finish.reflection
                              * cast_ray(ray, recursion_depth-1);
        }

        final_color += (1.0f - closest_hit.obj->finish.reflection -
                            closest_hit.obj->pigment.color.w )
                       * calcLighting_all(closest_hit.obj, N, pos);
        
    }

    return final_color;
}


// returns in range -1, 1 (not sure if incusive)
float randFloat() {
    return ((float) rand() / RAND_MAX);
}



// === ray marching ===

float sin_func(float x, float z) {
    return sin(x) * sin(z);
}

vec3 func_norm(float x, float z) {
    return glm::normalize(vec3(-sin(z) * cos(x), 1.0, -sin(x) * cos(z)));
}

bool ray_march_intersect(const Ray &ray, float &resT) {


    // from iquilezles.org terrain marching article 
    const float delt = 0.1f;
    const float mint = 0.0f;
    const float maxt = 100.0f;

    for(float t = mint; t < maxt; t += delt) {
        const vec3 p = ray.p0 + ray.d*t;
        if( p.y < sin_func( p.x, p.z ) )
        {
            resT = t - 0.5f*delt;
            return true;
        }
    }
    return false;

}




vec3 march_ray(const Ray &ray) {

    float t;

    vec3 N;
    

    if (ray_march_intersect(ray, t)) {
        const vec3 pos = ray.p0 + ray.d * t;

        vec3 N = func_norm(pos.x, pos.z);
        
        return calcLighting_all(g_geom[0], N, pos);
    }

    return vec3(0.0f);
}


void render(int samples_per_pixel) {
    Ray *ray;

    vec3 color = vec3(0.0);

    for (int y=0; y < g_image_height; y++) { 
        for (int x=0; x < g_image_width; x++) {

            color *= 0.0f;
            if (samples_per_pixel > 1) {
                for (int i=0; i < samples_per_pixel; i++) {

                    float dx = 0.5 * randFloat();
                    float dy = 0.5 * randFloat();

                    ray = g_camera->genRay(x+dx, y+dy);

                    color += march_ray(*ray);

                    delete ray;
                }
            } else {
                ray = g_camera->genRay(x, y);
                color = march_ray(*ray);
                delete ray;
            }

            // take average
            g_image[x][y] = (1.0f/samples_per_pixel) * color;
        }
        printf("\r %.3f done", 100 * ((float) y) / g_image_height);
        cout.flush();
    }

    cout << endl;
}

int main(int argc, char* argv[]) {

    if (argc < 4) {
        cerr << "usage: " << argv[0] <<
            " width height input.pov [samples per pixel]\n";
        exit(1);
    }

    g_image_width = atoi(argv[1]); 
    g_image_height = atoi(argv[2]); 

    if (g_image_width <= 0 || g_image_height <= 0) {
        cerr << "Error: Width and height must be positive\n";
        exit(1);
    }

    calcLighting = calcLightingPhong;

    string fname(argv[3]);
    parse_pov(fname);
    cout << "g_geom size: " << g_geom.size() << endl;


    // print objects
    /*
    for (unsigned int i=0; i<theObjects.size(); i++) {
        cout << endl << endl << theObjects[i]->name << ":\n";
        theObjects[i]->print_properties();
    }
    */

    cout << "w: " << g_image_width << " h: " << g_image_height
         << " fname: " << fname << endl;

    g_image = init_image(g_image_width, g_image_height);

    g_camera->setImageDimention(g_image_width, g_image_height);

    // g_obj_tree = new BVHNode(g_geom);
    // g_obj_tree->print();

    // Anti aliasing
    int samples_per_pixel = 9; // Zoe wants 9

    if (argc > 4) {
        samples_per_pixel = atoi(argv[4]);
    }
    // the main thing
    render(samples_per_pixel);



    // image test
    // draw_circle(g_image_height/3);

    // works only with ppm now
    string outfile_name(fname + ".ppm");
	write_image(g_image, outfile_name);
	

    return 0;
}
