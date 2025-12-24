#ifndef __scene_h_
#define __scene_h_

#include "../types.h"
#include "camera.h"
#include "object.h"
#include "light.h"
#include <vector>
#include <memory>

class Scene
{
private:
    /* data */
public:
    std::vector<std::shared_ptr<RenderObject>> objects;
    std::vector<std::shared_ptr<Light>> lights;
    std::shared_ptr<Camera> main_camera;
    Scene(Camera camera);
    Scene(std::shared_ptr<Camera> camera);
    ~Scene();

    void add_object(RenderObject& obj);
    void add_object(Sphere& obj);
    void add_ligth(Light& light);
};

Scene default_scene(int width, int height);

#endif