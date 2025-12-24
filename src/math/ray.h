#ifndef __ray_h_
#define __ray_h_

# include "../types.h"
# include <iostream>

class Vec3f {
private:
public:
    float x;
    float y;
    float z;

    Vec3f() : x(0), y(0), z(0){}
    Vec3f(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3f operator+(const float number) const;
    Vec3f operator+(const Vec3f& vec) const;
    Vec3f operator*(const float number) const;
    Vec3f operator*(const Vec3f& vec) const;
    Vec3f operator/(const float number) const;
    Vec3f operator-() const;
    Vec3f operator-(const Vec3f& vec) const;
    Vec3f operator-(const float number) const;
    friend Vec3f operator*(float number, const Vec3f& vec);
    friend Vec3f operator-(float number, const Vec3f& vec);

    friend std::ostream& operator<<(std::ostream& os, const Vec3f& vec);
    float lengthSquared();
    Vec3f normalize();
};

# include "render_math.h"
# include "../sceneData/object.h"
# include "../sceneData/scene.h"
# include <limits>

Vec3f cast_ray(Vec3f orig, Vec3f dir, Scene &scene, unsigned short *Xi);
float dot(Vec3f v1, Vec3f v2);
Vec3f reflect(Vec3f& vec, Vec3f& normal);
float absDot(Vec3f& vec1, Vec3f& vec2);
Vec3f cross(const Vec3f& a, const Vec3f& b);
#endif