#ifndef PHI_UTILS_H_
#define PHI_UTILS_H_

#include <cstdint>
#include <string>


void phi_sleep(uint32_t millisec);
std::string get_extension(const std::string& filename);

inline void split_rgb(uint32_t rgbcolor,
                      uint8_t& red, uint8_t& green, uint8_t& blue)
{
    red = rgbcolor >> 24;
    green = rgbcolor >> 16;
    blue = rgbcolor >> 8;
}

inline uint32_t to_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t rgb = 0;

    rgb |= uint32_t(red) << 24;
    rgb |= uint32_t(green) << 16;
    rgb |= uint32_t(blue) << 8;

    return rgb;
}




#endif // PHI_UTILS_H_
