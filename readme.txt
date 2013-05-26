



To compile, just run "make -B". Everything is included.

To run: ./raytrace width height scene.pov [rays per pixel]

This will produce an output file scene.pov.ppm



Part 4
======

* Implemented BVH, construction and intersection for spheres only.
* no intersection for boxes
* anti-aliasing (9 samples per pixel default.)

Run times for:

800x600 gnarly.pov: 3 seconds   (6 level recursion, shadows off, AA off)
800x600 balls2.pov: 5 seconds   (6 level recursion, shadows off, AA off)

640x480 balls2.pov: 27 seconds with 9


machine: 64 bit, 2.4GHz core 2 duo





Part 3
======

Refractions mostly work.


Images in images/ with renders of
- simple_refract.pov
- recurse_simp.pov
- recurses.pov
- simple_tri.pov
- ugly_part.pov

Some interesting images are in images/interesting/
Most notably, elongated_refract.png and simple_refract_lens.png

recurses.png took 2m:24s to render on my laptop (2.4g core 2 duo but it only
        uses 1 core)








done for p2:
	- specular for phong
	- reflections
	- obj transforms
	- cam transforms
	- handin renders of simp_cam and simp_reflect











