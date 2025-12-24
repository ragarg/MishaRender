#include "ray.h"
#include "../sceneData/scene.h"
#include "math.h"
#include "random.h"
#include <iostream>
#include <chrono> 
# include <random>

unsigned int seed = std::chrono::steady_clock::now().time_since_epoch().count();
std::mt19937 mt_engine(seed);

Vec3f Vec3f::operator+(const float number) const {
    return Vec3f(x + number, y + number, z + number);
}

Vec3f Vec3f::operator+(const Vec3f& vec) const {
    return Vec3f(x + vec.x, y + vec.y, z + vec.z);
}

Vec3f Vec3f::operator*(const float number) const {
    return Vec3f(x * number, y * number, z * number);
}

Vec3f Vec3f::operator*(const Vec3f& vec) const {
    return Vec3f(x * vec.x, y * vec.y , z * vec.z);
}

Vec3f Vec3f::operator/(const float number) const {
    return Vec3f(x / number, y / number, z / number);
}

Vec3f Vec3f::operator-(const Vec3f& vec) const {
    return Vec3f(x - vec.x, y - vec.y, z - vec.z);
}

Vec3f Vec3f::operator-(const float number) const {
    return Vec3f(x - number, y - number, z - number);
}

Vec3f Vec3f::operator-() const{
    return Vec3f(-x, -y, -z);
}

Vec3f operator*(float number, const Vec3f& vec) {
    return Vec3f(vec.x * number, vec.y * number, vec.z * number);
}

Vec3f operator-(float number, const Vec3f& vec) {
    return Vec3f(vec.x - number, vec.y - number, vec.z - number);
}

std::ostream& operator<<(std::ostream& os, const Vec3f& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

float Vec3f::lengthSquared() {
    return x * x + y * y + z * z;
}

Vec3f Vec3f::normalize(){
    float inv_len = 1.f/SafeSqrt(this->lengthSquared());// Q_rsqrt(this->lengthSquared());

    return (Vec3f(x * inv_len, y * inv_len, z * inv_len));
}

float dot(Vec3f v1, Vec3f v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3f reflect(Vec3f& vec, Vec3f& normal) {
    return (vec - 2.f * dot(vec, normal) * normal).normalize();
}

float absDot(Vec3f& vec1, Vec3f& vec2){
    return std::abs(dot(vec1, vec2));
}

Vec3f cross(const Vec3f& a, const Vec3f& b) {
    return Vec3f(
        a.y * b.z - a.z * b.y,   // X компонента
        a.z * b.x - a.x * b.z,   // Y компонента
        a.x * b.y - a.y * b.x    // Z компонента
    );
}

Vec3f deviate_reflection(Vec3f &dir, Vec3f &normal, Vec3f wp, float roughness ) {
    Vec3f tangent;
    if (dot(dir, normal) > 0.99f) {
        tangent = (dir * Vec3f(1.f, 0.f, 0.f)).normalize();
        if (tangent.lengthSquared() < 0.001f)
            tangent = tangent = (dir * Vec3f(0.f, 1.f, 0.f)).normalize();
    }
    else {
        tangent = (dir * normal).normalize();
    }

    Vec3f bitangent = roughness * (normal * tangent).normalize();

    Vec3f deviation_in_plane = roughness * (wp.x * tangent + wp.y * bitangent);

    Vec3f deviation_normal = 0.1f * roughness * wp.z * normal;

    Vec3f total_deviation = deviation_in_plane + deviation_normal;



    Vec3f R_deviated = (dir + total_deviation).normalize();

    if (dot(R_deviated, normal) < 0.f)
        R_deviated = (R_deviated - 2.f * dot(R_deviated, normal) * normal).normalize();

    return R_deviated;
}

Vec3f cast_ray(Vec3f orig, Vec3f dir, Scene &scene, unsigned short *Xi) {
    float dist = std::numeric_limits<float>::max();

    Vec3f result = Vec3f(0.0f, 0.0f, 0.0f);
    Vec3f throughput = Vec3f(1.0f, 1.0f, 1.0f);

    for (int bounceIndex = 0; bounceIndex < 10; bounceIndex++) {
        // find intersect with object
        int find = -1;
        for (int i = 0; i < scene.objects.size(); ++i) {
            auto obj = scene.objects[i];
            float sphere_dist = std::numeric_limits<float>::max();
            auto [intersection, d] = obj->ray_intersect(orig, dir, sphere_dist);
            if (intersection && dist > d) {
                find = i;
                dist = d ;
            }
        }

        if (find != -1) {
            
            auto obj = scene.objects[find];
            // return obj->color;
            Vec3f intersect_point = orig + dir * (dist - 0.0001f);
            Vec3f normal = obj->get_normal(intersect_point);
            // Vec3f nl = normal * sign(-dot(normal, dir));
            Vec3f le = obj->Le() * 1000.f;
            
            float r2 = RandomFloat01(mt_engine);
			// Vec3f d = jitter(nl, 2.f*PI*RandomFloat01(mt_engine), sqrt(r2), sqrt(1.f - r2)).normalize();
            Vec3f ref = reflect(dir, normal);
            Vec3f rand = (RandomUnitVector(mt_engine) + normal).normalize();

            orig = intersect_point;
            dir = mix(ref, rand, obj->roughness * obj->roughness);

            float fcos = absDot(dir, normal);

			result = result + throughput * le * fcos * (1.f / (4.f * PI));
			throughput = throughput * obj->color;
        }
        else {
            result = result + Vec3f(0.2f, 0.2f, 0.2f) * throughput;
            break;
        }
    }
    return result;

    // return Vec3f(0.5f, 0.5f, 0.5f);
    // return Vec3f(1.5f, 1.5f, 1.5f);
    
}