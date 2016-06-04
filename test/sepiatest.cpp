#include <cstdio>
#include <algorithm>
#include <cstdint>



int main()
{
    int w = 16096;
    int h = 8048;
    uint32_t* buffer = new uint32_t[w * h];

    int width = w;
    int height = h;

    #pragma omp parallel for
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            uint8_t* pixel = (uint8_t*)(buffer + (y * width + x));
            uint8_t r = *(pixel + 0);
            uint8_t g = *(pixel + 1);
            uint8_t b = *(pixel + 2);

            *(pixel++) = std::min(r * 0.343 + g * 0.686 + b * 0.168, 255.0);
            *(pixel++) = std::min(r * 0.272 + g * 0.534 + b * 0.131, 255.0);
            *(pixel++) = std::min(r * 0.393 + g * 0.769 + b * 0.189, 255.0);
        }
    }

    return (0);
}
