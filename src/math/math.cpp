#include "render_math.h"

float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // страшное дробное хакерство на битовом уровне
	i  = 0x5f3759df - ( i >> 1 );               // что за чёрт?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1-я итерация
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2-я итерация, можно убрать

	return y;
}

float maxf(float a, float b) {
    return a > b ? a: b;
}

Vec3f maxf(float a, Vec3f& b) {
    return Vec3f(maxf(a, b.x), maxf(a, b.y), maxf(a, b.z));
}

float minf(float a, float b) {
    return a < b ? a: b;
}

Vec3f minf(float a, Vec3f& b) {
    return Vec3f(minf(a, b.x), minf(a, b.y), minf(a, b.z));
}

Vec3f mix(Vec3f& a, Vec3f& b, float r) {
    return a * (1.f - r) + b * (r);
}

float sign(float a) { return a >=0 ? 1.f: -1.f; }

float SafeSqrt(float x) { return std::sqrt(std::max(0.f, x)); }