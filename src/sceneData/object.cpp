#include "object.h"
#include <iostream>

RenderObject::RenderObject() : name("Name"), color(Vec3f()) {
}

RenderObject::RenderObject(Vec3f &color) : name("Name"), color(color) {
}

RenderObject::RenderObject(Vec3f &color, bool is_ligth) : name("Name"), color(color) {
    if (is_ligth) {
        le = color;
    }
}

RenderObject::~RenderObject() {
}

Vec3f RenderObject::get_normal(Vec3f point) const {
    return Vec3f(0.f, 0.f, 1.f);
}

float RenderObject::bsdf(Vec3f wo, Vec3f wi) const {
    return 1.0;
}

Vec3f RenderObject::Le() const {
    return le * 0.1f;
}

std::tuple<bool,float> RenderObject::ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const { return {false, t0}; }


Sphere::Sphere(Vec3f &c, const float &r) : RenderObject(), center(c), radius(r){
}

Sphere::Sphere(Vec3f& color, Vec3f &c, const float &r) : RenderObject(color), center(c), radius(r){
}

Sphere::Sphere(Vec3f& color, Vec3f &c, const float &r, bool is_ligth) : RenderObject(color, is_ligth), center(c), radius(r){
}

Vec3f Sphere::get_normal(Vec3f point) const {
    // std::cout << point << " " << (-point + center).normalize() << "\n";
    return (point - center).normalize();
}

std::tuple<bool,float> Sphere::ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const {
    Vec3f& L = center - orig;
    float tca = dot(L, dir);
    float d2 = dot(L,L) - tca*tca;
    if (d2 > radius*radius) return {false, t0};
    float thc = sqrtf(radius*radius - d2);
    // Ближняя и дальняя точки пересечения
    float t1 = tca - thc;
    float t2 = tca + thc;
    
    // Выбираем ближайшее положительное пересечение
    if (t1 > 0 && t1 < t2) {
        t0 = t1;
        return {true, t0};
    } else if (t2 > 0) {
        t0 = t2;
        return {true, t0};
    } else {
        // Обе точки пересечения позади начала луча
        return {false, t0};
    }

}

Sphere::~Sphere() {
}

Plane::Plane(Vec3f &normal, Vec3f &point) : RenderObject(), normal(normal.normalize()), point(point) {
}

Plane::Plane(Vec3f &color, Vec3f &normal, Vec3f &point) : RenderObject(color), normal(normal.normalize()), point(point) {
}

Plane::Plane(Vec3f &color, Vec3f &normal, Vec3f &point,  bool is_ligth) : RenderObject(color, is_ligth), normal(normal.normalize()), point(point) {
}

Vec3f Plane::get_normal(Vec3f point) const {
    // std::cout << normal << "\n";
    return normal;
}

std::tuple<bool,float> Plane::ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const {
    float denom  =  normal.x * dir.x + normal.y * dir.y + normal.z * dir.z;

    if (std::fabs(denom) < 1e-6)
        return {false, t0};

    float numer = -(normal.x * (orig.x - point.x) + normal.y * (orig.y - point.y) + normal.z * (orig.z - point.z));
    
    float t = numer / denom;
    if (t < 0.f)
        return {false, t0};
    t0 = t;
    return {true, t0};
}

Plane::~Plane() {
}