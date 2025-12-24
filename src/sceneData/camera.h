#ifndef __camera_h_
#define __camera_h_

# include "../types.h"
# include "../math/ray.h"
# include "../render/render.h"

class Camera
{
private:
public:
    int width;
    int height;

    float fov;

    Vec3f dir;

    Camera();
    Camera(int& width, int& height);
    ~Camera();
};


#endif