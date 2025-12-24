#include "scene.h"
#include <iostream>

Scene::Scene(Camera camera) : main_camera(std::make_shared<Camera>(std::move(camera)))
{
}

Scene::Scene(std::shared_ptr<Camera> camera) : main_camera(camera)
{
}

Scene::~Scene()
{
}

void Scene::add_object(RenderObject& obj) {
    objects.push_back(std::make_shared<RenderObject>(obj));  
}

void Scene::add_object(Sphere& obj) {
    objects.push_back(std::make_shared<Sphere>(obj));  
}

void Scene::add_ligth(Light& light) {
    lights.push_back(std::make_shared<Light>(light));  
}

Scene default_scene(int width, int height) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(width, height);
    Scene scene = Scene(camera);

    // Spheres
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Vec3f(1.0f, 0.2f, 0.2f), Vec3f(-3.0f, -2.0f, -10.f), 2.f);
    scene.objects.push_back(sphere);
    sphere->roughness = 0.5; 
    std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Vec3f(1.1f, 1.2f, 1.1f), Vec3f(0.0f, 13.5f, -10.f), 10.f, true);
    scene.objects.push_back(sphere2);
    std::shared_ptr<Sphere> sphere3 = std::make_shared<Sphere>(Vec3f(0.2f, 1.0f, 0.2f), Vec3f(5.0f, -2.0f, -10.f), 2.f, false);
    scene.objects.push_back(sphere3);

    sphere3->roughness = 1.0; 

    //Planes
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(Vec3f(0.0f, 0.2f, 0.7f), Vec3f(0.0f, 0.0f, 1.f), Vec3f(0.0f, 0.0f, -12.f), false); 
    scene.objects.push_back(plane);
    std::shared_ptr<Plane> plane1 = std::make_shared<Plane>(Vec3f(0.2f, 0.0f, 0.7f), Vec3f(-1.f, 0.0f, 0.f), Vec3f(6.0f, 0.0f, 0.f), false); 
    scene.objects.push_back(plane1);
    std::shared_ptr<Plane> plane2 = std::make_shared<Plane>(Vec3f(0.0f, 0.0f, 0.7f), Vec3f(1.f, 0.0f, 0.f), Vec3f(-5.0f, 0.0f, 0.f), false); 
    scene.objects.push_back(plane2);
    std::shared_ptr<Plane> plane4 = std::make_shared<Plane>(Vec3f(0.2f, 0.2f, 0.5f), Vec3f(0.0f, -1.0f, 0.f), Vec3f(0.0f, 4.0f, 0.f), false); 
    scene.objects.push_back(plane4);
    std::shared_ptr<Plane> plane3 = std::make_shared<Plane>(Vec3f(0.2f, 0.2f, 1.0f), Vec3f(0.0f, 1.0f, -0.f), Vec3f(0.0f, -5.0f, 0.f), false); 
    scene.objects.push_back(plane3);

    plane->roughness = 1.0; 
    plane1->roughness = 1.0; 
    plane2->roughness = 1.0; 
    plane3->roughness = 1.0; 
    plane4->roughness = 1.0; 
    return scene;
}