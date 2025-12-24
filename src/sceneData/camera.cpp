#include "camera.h"

Camera::Camera() {
    width = 1000;
    height = 500;

    fov = FOV;

    this->dir = Vec3f();
}

Camera::Camera(int& width, int& height) : width(width), height(height) {
    fov = FOV;

    dir = Vec3f();
}

Camera::~Camera() {
}
