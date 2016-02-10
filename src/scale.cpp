#include "scale.h"
#include <cmath>


uint32_t* scale(uint32_t* buffer, int& src_w, int& src_h, int dst_w, int dst_h, bool modify)
{
    float w_ratio = src_w / dst_w;
    float h_ratio = src_h / dst_h;

    //Image* dst_image = create_image(dst_w, dst_h);
    uint32_t* dst_buffer = new uint32_t[dst_w * dst_h];

    for (int y = 0; y < dst_h; y++)
    {
        for (int x = 0; x < dst_w; x++)
        {
            int src_x = floor(x * w_ratio);
            int src_y = floor(y * h_ratio);
            dst_buffer[y * dst_w + x] = buffer[src_y * src_w + src_x];
        }
    }

    if (modify)
    {
        delete buffer;
        buffer = dst_buffer;
        src_w = dst_w;
        src_h = dst_h;
        return NULL;
    }

    return dst_buffer;
}
