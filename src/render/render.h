#ifndef __render_h_
#define __render_h_

#define FOV 1.5f

# include "../types.h"
# include <vector>
# include "../math/render_math.h"
# include "../math/ray.h"

std::vector<Vec3f> render(Scene scene);

#endif