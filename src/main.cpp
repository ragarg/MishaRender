#include "render/render.h"
#include "sceneData/scene.h"
#include "math/ray.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char *argv[]) {
    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);

    // Scene* scene;

    // TODO: write parse
    // if (argc == 4) {
    //     scene = parse();
    // }
    // else {
        Scene scene = default_scene(width, height);
    // }

    // TODO: write output module
    std::vector<Vec3f> framebuffer = render(scene);

    std::ofstream ofs("./out.ppm", std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    
    for (size_t j = 0; j < height; ++j) {
        for (size_t i = 0; i < width; ++i) {
            ofs << (unsigned char)(255.0 * maxf(0.f, minf(1.f, framebuffer[i+j*width].x)));
            ofs << (unsigned char)(255.0 * maxf(0.f, minf(1.f, framebuffer[i+j*width].y)));
            ofs << (unsigned char)(255.0 * maxf(0.f, minf(1.f, framebuffer[i+j*width].z)));
        }
    }
    return 0;
}