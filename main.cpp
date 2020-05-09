#include "colour.h"

#include <iostream>

int main()
{
    const int img_width = 256;
    const int img_height = 256;
    const float max_val = 255.999;

    std::cout << "P3\n"
              << img_width << ' ' << img_height << "\n255\n";

    for (int j = img_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < img_width; ++i)
        {
            colour pixel_colour(float(i) / (img_width - 1), float(j) / (img_height - 1), 0.25);
            write_colour(std::cout, pixel_colour);
        }
    }
    std::cerr << "\nDone.\n";
}