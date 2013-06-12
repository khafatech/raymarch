



To compile, just run "make -B". Everything is included.

To run: ./raytrace width height scene.pov [rays per pixel]

If no rays per pixel are given, it defaults to 9.

This will produce an output file scene.pov.ppm


Part 5
=======

Monte Carlo kind of works.

Images in images_MonteCarlo.

simple_mc.pov has a green horizontal plane, and a white vertical plane.

I turned off ambient.

Bugs:
There's an artifac on the z axis as in the valentine2_monteCarlo.png.


Part 4
======

* Implemented BVH, construction and intersection
* no shading for boxes
* anti-aliasing (9 samples per pixel default.)

Run times for:

640x480 gnarly.pov: 10.3 seconds   (all lights, 6 level recursion)

640x480 balls2.pov: 8.3 seconds (all lights, 6 level recursion)

640x480 bunny_large_tris.pov: 6.6 seconds (9AA, all lights, 6 level recursion)

* no shadows:
    800x600 gnarly.pov: 3 seconds   (first light, 6 level recursion, AA off)
    640x480 gnarly.pov: 15 seconds   (all lights, 6 level recursion, 9xAA)

    800x600 balls2.pov: 5 seconds   (first light, 6 level recursion, AA off)
    640x480 balls2.pov: 27 seconds (3 lights, 6 level recursion, 9xAA)


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











