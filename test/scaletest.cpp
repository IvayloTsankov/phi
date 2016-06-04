#include "../src/effects.h"
#include <cstdio>


int main()
{
    int w = 320;
    int h = 240;
    uint32_t* image = new uint32_t[w * h];
    for(int y = 0; y < h; ++y)
    {
        for(int x = 0; x < w; ++x)
        {
            image[y * w + x] = y * 100 + x;
        }
    }

    int nw = w / 2;
    int nh = h / 2;
    uint32_t* new_image = scale(image, w, h, nw, nh);
    for(int y = 0; y < nh; ++y)
    {
        for(int x = 0; x < nw; ++x)
        {
            printf("%u ", new_image[y * nh + x]);
        }

        printf("\n");
    }

    return (0);
}
