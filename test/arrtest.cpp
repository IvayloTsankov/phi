#include "slog/slog.h"

uint32_t* get_image(int width, int height)
{
    return new uint32_t[width * height];
}

void free_image(uint32_t* image)
{
    delete image;
}

uint32_t* test(int w, int h)
{
    uint32_t* arr = get_image(w, h);

    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            arr[i * w + j] = 0xFF000000;
        }
    }

    return arr;
}

int main()
{
    int width = 640;
    int height = 480;
    uint32_t* image = test(width, height);
    
    image[0] = 0x00FF0000;
    image[1] = 0x0000FF00;
    free_image(image);

    return (0);
}
