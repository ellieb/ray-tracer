#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

#include <iostream>

void write_colour(std::ostream &out, colour pixel_colour)
{
    // Write the translated [0, 255] value of each colour component
    const float max_val = 255.999;
    out << static_cast<int>(max_val * pixel_colour.x()) << ' '
        << static_cast<int>(max_val * pixel_colour.y()) << ' '
        << static_cast<int>(max_val * pixel_colour.z()) << '\n';
}

#endif