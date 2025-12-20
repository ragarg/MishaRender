#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
// #include "geometry.h"

class Vec3f
{
private:
public:
    float x;
    float y;
    float z;
    Vec3f(){}
    Vec3f(float x, float y, float z) : x(x), y(y), z(z) {}
    Vec3f operator+(const float number){
        this->x += number;
        this->y += number;
        this->z += number;

        return *this;
    }
    Vec3f operator*(const float number){
        this->x *= number;
        this->y *= number;
        this->z *= number;

        return *this;
    }
    Vec3f operator+(const int number){
        this->x += float(number);
        this->y += float(number);
        this->z += float(number);

        return *this;
    }
    Vec3f operator*(const int number){
        this->x *= float(number);
        this->y *= float(number);
        this->z *= float(number);

        return *this;
    }
};

float max(float a, float b) {
    return a > b ? a: b;
}

Vec3f max(float a, Vec3f& b) {
    return Vec3f(max(a, b.x), max(a, b.y), max(a, b.z));
}

float min(float a, float b) {
    return a < b ? a: b;
}

Vec3f min(float a, Vec3f& b) {
    return Vec3f(min(a, b.x), min(a, b.y), min(a, b.z));
}

void render(int width, int height) {
    std::vector<Vec3f> framebuffer(width*height);

    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            framebuffer[i+j*width] = Vec3f(j/float(height),i/float(width), 128);
        }
    }

    std::ofstream ofs("./out.ppm", std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    // std::ofstream ofs("./out.ppm", std::ios::binary);
    for (size_t i = 0; i < height*width; ++i) {
        ofs << (unsigned char)(255.0 * max(0.f, min(1.f, framebuffer[i].x)));
        ofs << (unsigned char)(255.0 * max(0.f, min(1.f, framebuffer[i].y)));
        ofs << (unsigned char)(255.0 * max(0.f, min(1.f, framebuffer[i].z)));
    }
}

int main(int argc, char *argv[]) {
    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);
    render(width, height);
    return 0;
}