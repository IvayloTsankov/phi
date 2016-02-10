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

void phi_sleep(uint32_t millisec)
{
#if defined (_WIN32)
    Sleep(millisec);
#else
    usleep(millisec * 1000);
#endif // (_WIN32)
}
