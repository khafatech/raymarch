// cs174, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <100, 6, 10.2>
  up        <0,  1,  0>
  right     <-1.33333, 0, 0>
  look_at   <100, 0, 100>
}


light_source {<-100, 100, 0> color rgb <1.5, 1.49, 1.05>}

light_source {<100, 100, 0> color rgb <0.0, 0.0, 0.2>}

// light_source {<10, 10, 0> color rgb <1.0, 0.0, 0.0>}

sphere { <0, 0, 0>, 1
  pigment { color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.5 diffuse 1 roughness 0.01}
  scale <2, 3, 4>
  translate <10, 0, 0>
}

plane {<0, 1, 0>, -0.5
      pigment {color rgb <0.5, 1.5, 0.5>}
      finish {ambient 0.4 diffuse 0.8}
}




