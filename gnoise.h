
#ifndef GNOISE_H
#define GNOISE_H

#include "glm/glm.hpp"


#define LERP(t,x0,xl) ((x0) + ((xl)-(x0))*(t))

float gnoise(float x, float y, float z);

void normal_gnoise(glm::vec3 &N, float x, float y, float z);

float gnoise(glm::vec3 v);


#endif
