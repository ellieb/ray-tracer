#include <iostream>

#include "camera.h"
#include "colour.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "tracer.h"

double hit_sphere(const point3 &center, double radius, const ray &r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / (a);
    };
}

colour ray_colour(const ray &r, const hittable &world, int depth) {
    // Creates a gradient
    hit_record rec;
    // If we've exceeded the ray bounce limit, no more light is gathered
    if (depth <= 0) return colour(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        colour attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_colour(scattered, world, depth - 1);
        return colour(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

int main() {
    const auto aspect_ratio = 16.0 / 9.0;
    const int img_width = 384;
    const int img_height = static_cast<int>(img_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const float max_val = 255.999;
    const int max_depth = 50;

    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5,
                                  make_shared<lambertian>(colour(.1, .2, .5))));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100,
                                  make_shared<lambertian>(colour(.8, .8, 0.))));
    world.add(make_shared<sphere>(point3(1, 0, -1), 0.5,
                                  make_shared<metal>(colour(.8, .6, .2), 0.3)));
    world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5,
                                  make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(point3(-1, 0, -1), -0.45,
                                  make_shared<dielectric>(1.5)));

    /*     auto R = cos(pi / 4);
        hittable_list world;
        world.add(make_shared<sphere>(point3(-R, 0, -1), R,
                                      make_shared<lambertian>(colour(0, 0,
       1)))); world.add(make_shared<sphere>(point3(R, 0, -1), R,
                                      make_shared<lambertian>(colour(1, 0,
       0))));
     */
    point3 lookfrom(3, 3, 2);
    point3 lookat(0, 0, -1);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = (lookfrom - lookat).length();
    auto aperture = 2.0;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture,
               dist_to_focus);

    for (int j = img_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < img_width; ++i) {
            colour pixel_colour(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = (i + random_double()) / (img_width - 1);
                auto v = (j + random_double()) / (img_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_colour += ray_colour(r, world, max_depth);
            }
            write_colour(std::cout, pixel_colour, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}