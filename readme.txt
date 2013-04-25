

To compile, just run make. Everything is included.


Raytracer part1

- draws just pigments of spheres and planes


loop over pixels:
    - get ray in world coordinates
    - for each geom object:
        find intersection


Coveats:

* output is name.pov.ppm


TODO for p2:

	- specular for phong
	- another shading model
	- reflections
	- obj transforms
	- cam transforms
	- handin renders of simp_cam and simp_reflect


## bug:
* ray not intersecting with sphere when using translate (xmat_i)
	(using the method of transforming the ray into object coords)








