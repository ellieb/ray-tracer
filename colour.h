#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>

#include "vec3.h"

void write_colour(std::ostream &out, colour pixel_colour,
                  int samples_per_pixel) {
    auto r = pixel_colour.x();
    auto g = pixel_colour.y();
    auto b = pixel_colour.z();

    // Divide the color total by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Write the translated [0, 255] value of each colour component
    const float max_val = 256;
    out << static_cast<int>(max_val * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(max_val * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(max_val * clamp(b, 0.0, 0.999)) << '\n';
}

#endif