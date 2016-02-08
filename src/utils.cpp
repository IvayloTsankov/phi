#include "utils.h"

#if defined (_WIN32)
#   include <WinBase.h>
#else
#   include <unistd.h>
#endif // (_WIN32)

inline uint32_t* alloc_image_buffer(int width, int height)
{
    return new uint32_t[width * height];
}

void free_image_buffer(uint32_t* img_buffer)
{
    delete img_buffer;
}

uint32_t* scale(uint32_t* src_image, int src_w, int src_h,
                int dst_w, int dst_h)
{
    uint32_t* dst_image = alloc_image_buffer(dst_w, dst_h);
    for(int y = 0; y < dst_h; ++y)
    {
        for(int x = 0; x < dst_w; ++x)
        {
            dst_image[y * dst_h + x] = src_image[(y * src_h / dst_h) + (x * src_w / dst_w)];
        }
    }

    return dst_image;
}

void phi_sleep(uint32_t millisec)
{
#if defined (_WIN32)
    Sleep(millisec);
#else
    usleep(millisec * 1000);
#endif // (_WIN32)
}
