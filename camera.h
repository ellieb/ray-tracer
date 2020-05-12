#ifndef CAMERA_H
#define CAMERA_H

#include "tracer.h"

class camera {
   public:
    camera(point3 lookfrom, point3 lookat, vec3 vup,
           double vfov,  // vertical field-of-view in degrees
           double aspect_ratio) {
        origin = lookfrom;
        vec3 u, v, w;
        auto theta = degrees_to_radians(vfov);
        auto half_height = tan(theta / 2);
        auto half_width = aspect_ratio * half_height;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        lower_left_corner = origin - half_width * u - half_height * v - w;

        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
    }

    ray get_ray(double u, double v) const {
        return ray(origin,
                   lower_left_corner + u * horizontal + v * vertical - origin);
    }

   private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif