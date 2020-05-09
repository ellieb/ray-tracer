#include "vec3.h"
#include "colour.h"
#include "ray.h"

#include <iostream>

colour ray_colour(const ray &r)
{
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

int main()
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int img_width = 384;
    const int img_height = static_cast<int>(img_width / aspect_ratio);
    const float max_val = 255.999;

    std::cout << "P3\n"
              << img_width << ' ' << img_height << "\n255\n";

    point3 origin(0.0, 0.0, 0.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.25, 0.0);
    point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, 1);
    for (int j = img_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < img_width; ++i)
        {
            auto u = double(i) / (img_width - 1);
            auto v = double(j) / (img_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            colour pixel_colour = ray_colour(r);
            write_colour(std::cout, pixel_colour);
        }
    }
    std::cerr << "\nDone.\n";
}