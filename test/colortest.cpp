#include <cstdio>
#include <cstdint>
#include <inttypes.h>


void split_rgb(uint32_t rgbcolor,
               uint8_t& red, uint8_t& green, uint8_t& blue)
{
    red = rgbcolor >> 24;
    green = rgbcolor >> 16;
    blue = rgbcolor >> 8;
}

uint32_t to_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t rgb = 0;

    rgb |= uint32_t(red) << 24;
    rgb |= uint32_t(green) << 16;
    rgb |= uint32_t(blue) << 8;

    return rgb;
}

int main()
{
    uint32_t red = 0xFF000000;
    uint32_t green = 0x00FF0000;
    uint32_t blue = 0x0000FF00;
    uint32_t black = 0x00000000;
    uint32_t white = 0xFFFFFF00;

//     std::cout << red << std::endl;
//     return (0);

    uint8_t r, g, b;
    uint32_t rgbcolor = white;
    printf("rgbcolor: %u\n", rgbcolor);

    r = g = b = 0;
    split_rgb(rgbcolor, r, g, b);

    printf("red: " "%" PRIu8 "\n", r);
    printf("green: " "%" PRIu8 "\n", g);
    printf("blue: " "%" PRIu8 "\n", b);

    uint32_t rgb = to_rgb(r, g, b);
    printf("rgb: %u\n", rgb);

    return (0);
}
