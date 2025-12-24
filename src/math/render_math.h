#ifndef __math_h_
#define __math_h_

# include "../types.h"
# include <cmath>
# include "ray.h"
// # include <iostream>
// # include <fstream>
// # include <vector>
// # include <cstdlib>
// # include <string>

# define PI 3.14159265359
# define PI2 6.28318530718

float Q_rsqrt( float number );

float maxf(float a, float b);
Vec3f maxf(float a, Vec3f& b);
float minf(float a, float b);
Vec3f minf(float a, Vec3f& b);
Vec3f mix(Vec3f& a, Vec3f& b, float r);
float SafeSqrt(float x);
float sign(float a);
#endif