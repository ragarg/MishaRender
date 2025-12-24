#include "render.h"
#include "../math/ray.h"
#include "../sceneData/scene.h"
#include <thread>
#include <mutex>

#define NUM_TREADS 256
std::vector<Vec3f> render(Scene scene) {
    Camera camera = *scene.main_camera;
    int width = camera.width;
    int height = camera.height;

    std::vector<Vec3f> framebuffer(width*height);
    int sample = 10000;

    int num_threads = NUM_TREADS;//width*height;
    std::mutex m;

    std::vector<std::thread> threads(num_threads);

    std::cout << "sample: " << sample << "\n";
    auto thread_func = [&framebuffer, &width, &height, &sample, &camera, &scene, &m] (int thread_id) {       
        int thread_size = width*height / NUM_TREADS;

        for (int id = thread_size * thread_id; id < thread_size * (thread_id + 1); id++) {
            Vec3f result = Vec3f();
            int i = id % width;
            int j = id / height;
            for (int k = 0; k < sample; k++) {
                float dir_x = float(i - width/2.) + k / sample * 1.f;
                float dir_y = float(-j +  height/2. + 0.5) + k / sample * 1.f;
                float dir_z = float(-width/(2.f*tan(FOV/2.f)));
                Vec3f dir = Vec3f(dir_x, dir_y, dir_z).normalize();
                unsigned short Xi[3]={0,0,j*j*j};
                result = result + cast_ray(camera.dir, dir, scene, Xi);
            }
            // std::lock_guard<std::mutex> lock(m);
            framebuffer[i+j*width] = result / sample;
        }
        // std::lock_guard<std::mutex> unlock(m);
    };
    std::cout << "sample: " << sample << "\n";
    for (int thread_id = 0; thread_id < num_threads; ++thread_id){
        threads[thread_id] = std::thread(thread_func, thread_id);
    }
    std::cout << "sample: " << sample << "\n";
    for (int thread_id = 0; thread_id < num_threads; ++thread_id){
        threads[thread_id].join();
    }

    std::cout << "sample: " << sample << "\n";
    // for (int j = 0; j < height; j++) {
    //     for (int i = 0; i < width; i++) {
    //         framebuffer[i+j*width] = framebuffer[i+j*width] / float(sample);
    //     }
    // }

    return framebuffer;
}