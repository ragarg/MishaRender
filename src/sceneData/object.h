#ifndef __object_h_
#define __object_h_

# include "../types.h"
# include "../math/ray.h"
# include <string>

class RenderObject {
private:
    const std::string& name;
public:
    Vec3f color;
    Vec3f le;
    float roughness = 0.0;
    RenderObject();
    RenderObject(Vec3f &color);
    RenderObject(Vec3f &color, bool is_ligth);
    ~RenderObject();

    virtual Vec3f get_normal(Vec3f point) const;
    float bsdf(Vec3f wo, Vec3f wi) const;
    Vec3f Le() const;
    virtual std::tuple<bool,float> ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const;
};

class Sphere : public RenderObject {
private:

public:
    Vec3f center;
    float radius;
    Sphere(Vec3f &c, const float &r);
    Sphere(Vec3f &color, Vec3f &c, const float &r);
    Sphere(Vec3f& color, Vec3f &c, const float &r, bool is_ligth);
    ~Sphere();

    Vec3f get_normal(Vec3f point) const override;

    std::tuple<bool,float> ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const override;
};

class Plane : public RenderObject {
private:

public:
    Vec3f normal;
    Vec3f point;
    Plane(Vec3f &normal, Vec3f &point);
    Plane(Vec3f &color, Vec3f &normal, Vec3f &point);
    Plane(Vec3f &color, Vec3f &normal, Vec3f &point, bool is_ligth);
    ~Plane();

    Vec3f get_normal(Vec3f point) const override;

    std::tuple<bool,float> ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const override;
};
#endif