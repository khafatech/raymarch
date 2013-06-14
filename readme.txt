
Mustafa Khafateh

CSC 473 - Ray Tracer project



To compile, just run "make -B". Everything is included.

To run: ./raytrace width height scene.pov [rays per pixel]

If no rays per pixel are given, it defaults to 9.

This will produce an output file scene.pov.ppm

To toggle Monte-Carlo rendering, toggle the use_montecarlo boolean in raytrace.cpp and recompile.


Ray tracer updates 6/12/2013
=============================

Updated render of POV files:

- final1.pov, final2.pov, gnarly.pov, balls2.pov, recuse_simp2.pov (after changing "}}" to "} }")
	* Renders are in the images/ directory

- Fixed Global Illumination. looks good as expected. see images/final2_4xAA-14mins.png and images/interesting_montecarlo2.png


- Enabled shadows with BVH. I originally implemented shadows for P2 but disabled them when implementing the BVH and forgot to re enable them)


- Added shading and transforms for Boxes.
	(I had intersection working for bounding boxes,
	and wanted to use it for geometrical Boxes,
	but there was a subtle bug when a ray was inside the box, so it broke the BVH.)
	* I had all the transform functions in place (used for bounding xformed sphere)
	* the middle sphere in final1.pov has no specified specular and roughness.

- Improved how specular looks. Now bunny_large_tris.pov looks better.



- for recuse_simp2.pov, it renders correctly, but my pov parseer gets messed up by the "}}" at the end of the back wall planes. So I changed them to "} }". I took programming languages this quarter, so now I see how I could write a better parser.


Run times for (Without Monte Carlo, of course)

640x480 gnarly.pov: 10.3 seconds   (all lights, 6 level recursion)

640x480 balls2.pov: 8.3 seconds (all lights, 6 level recursion)

640x480 bunny_large_tris.pov: 6.6 seconds (9AA, all lights, 6 level recursion)




=========
Old notes
=========

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











