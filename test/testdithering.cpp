#include <cstdint>




int main()
{
    int w = 16096;
    int h = 8096;
    uint32_t* buffer = new uint32_t[w * h];
    int prop_error = 0;

    //#pragma omp parallel for
    for(int y = 0; y < h; ++y)
    {
        for(int x = 0; x < w; ++ x)
        {
            int pixel_i = (y * w) + x;
            int right = (y * w) + x + 1;
            int down = ((y + 1) * w) + x;
            int rdown = ((y + 1) * w) + x + 1;
            int ldown = ((y + 1) * w) + x - 1;

            uint32_t color = buffer[pixel_i];
            uint8_t* pixel = (uint8_t*)buffer + pixel_i;
            uint32_t gray = (*(pixel) + *(pixel + 1) + *(pixel + 2)) / 3;
//             uint8_t r, g, b;
//             r = color >> 24;
//             g = color >> 16;
//             b = color >> 8;
//             uint32_t gray = (r + g + b) / 3;
            uint32_t new_color = gray > 128 ? 0xFFFFFF00: 0x00000000;
            buffer[pixel_i] = new_color;

            prop_error += gray - new_color;
            prop_error = prop_error / 255 > 1 ? 255 : prop_error;
            if (x < w)
            {    
                uint8_t* np = (uint8_t*)(buffer + right);
                int prop_coef = 0.4375 * prop_error;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
            }

            if (y + 1 < h)
            {
                uint8_t* np = (uint8_t*)(buffer + down);
                int prop_coef = 0.3125 * prop_error;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
            }

            if (y + 1 < h && x + 1 < w)
            {
                uint8_t* np = (uint8_t*)(buffer + rdown);
                int prop_coef = 0.0625 * prop_error;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
            }

            if (y + 1 < h && x - 1 > 0)
            {
                uint8_t* np = (uint8_t*)(buffer + ldown);
                int prop_coef = 0.1875 * prop_error;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
                *(np++) += prop_coef;
            }
        }
    }
}
